#ifndef DIRECTORY_HEADER
#define DIRECTORY_HEADER

// local headers
#include "string_literal.hpp"
#include "string.hpp"
#include "types.hpp"
#include "path.hpp"
#include "stack.hpp"
#include "pair.hpp"
#include "unique_directory.hpp"



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- F I L E  S Y S T E M ------------------------------------------------

	namespace filesystem {


		// -- D I R E C T O R Y  I T E R A T O R  C L A S S -------------------

		template <bool recursive>
		class directory_iterator final {


			private:

				// -- private types -------------------------------------------

				/* pair type */
				using pair = xns::pair<xns::unique_directory,
									   xns::string>;

				/* container type */
				using container = xns::conditional<recursive, xns::stack<pair>,
															  pair>;

				/* directory entry type */
				using entity_ptr = struct dirent*;


				// -- private enums -------------------------------------------

				/* symbols enum */
				enum : char {
					POINT = 0x2E,
					SEPARATOR = 0x2F
				};


			public:

				// -- public types --------------------------------------------

				/* self type */
				using self = directory_iterator<recursive>;


				// -- public constructors -------------------------------------

				/* deleted default constructor */
				directory_iterator(void) = delete;

				/* nullptr constructor */
				inline directory_iterator(xns::null) noexcept
				: _container{}, _entity{nullptr} {}

				/* path constructor (non-recursive) */
				directory_iterator(const xns::string& path) requires (recursive == false)
				: _container{path, path}, _entity{nullptr} {

					// check opening failure
					if (xns::get<xns::unique_directory>(_container).is_open() == false) {
						return;
					}
					// get first entry
					operator++();
				}

				/* path constructor (recursive) */
				directory_iterator(const xns::string& path) requires (recursive == true)
				: _container{}, _entity{nullptr} {

					xns::unique_directory dir{path};
					// check opening failure
					if (dir.is_open() == false) { return; }
					// open directory
					_container.emplace(xns::move(dir), path);
					// get first entry
					operator++();
				}

				/* non-assignable class */
				NON_ASSIGNABLE(directory_iterator);

				/* destructor */
				~directory_iterator(void) noexcept = default;


				// -- public increment operators ------------------------------

				/* pre-increment operator (non-recursive) */
				auto operator++(void) noexcept -> self& requires (recursive == false) {
					// get next entry
					while ((_entity = ::readdir(xns::get<xns::unique_directory>(_container)))
							!= nullptr) {
						// check for directory '.' or '..'
						if (_entity->d_type != DT_DIR
						 || skip() == false) { break; }
					}
					return *this;
				}


				/* pre-increment operator (recursive) */
				auto operator++(void) -> self& requires (recursive == true) {

					while (_container.empty() == false) {

						// get next entry
						_entity = ::readdir(xns::get<xns::unique_directory>(_container.top()));

						// check for end of directory
						if (_entity == nullptr) {
							_container.pop();
							continue;
						}

						// check for directory
						if (_entity->d_type == DT_DIR) {

							// skip '.' and '..' directories
							if (skip() == true) { continue; }

							xns::string path{xns::get<xns::string>(_container.top())};
							path.append(SEPARATOR);
							#if defined(APPLE_OS)
								path.append(_entity->d_name, _entity->d_namlen);
						    #else
								path.append(_entity->d_name);
							#endif

							xns::unique_directory dir{path};

							// check opening failure (need to set errno like status)
							if (dir.is_open() == false) {
								write(STDERR_FILENO, "Error: could not open directory\n", 32);
								continue;
							}

							_container.emplace(xns::move(dir), xns::move(path));
							break;
						}

						break;
					}
					// return self reference
					return *this;
				}


				/* post-increment operator */
				directory_iterator& operator++(int) = delete;



				// -- comparison operators ------------------------------------

				/* equality operator */
				inline auto operator==(const directory_iterator& other) const noexcept -> bool {
					// compare inodes of entities
					#if defined(BSD_OS) || defined(APPLE_OS)
						return  _entity
							&&  other._entity
							&& (_entity->d_ino == other._entity->d_ino);
					#elif defined(LINUX_OS)
						return  _entity
							&&  other._entity
							&& (_entity->d_fileno == other._entity->d_fileno);
					#endif
				}

				/* inequality operator */
				inline auto operator!=(const directory_iterator& other) const noexcept -> bool {
					return operator==(other) == false;
				}

				/* null pointer equality operator */
				inline auto operator==(xns::null) const noexcept -> bool {
					return _entity == nullptr;
				}

				/* null pointer inequality operator */
				inline auto operator!=(xns::null) const noexcept -> bool {
					return _entity != nullptr;
				}


				// -- public boolean operators --------------------------------

				/* boolean operator */
				inline operator bool(void) const noexcept {
					return _entity != nullptr;
				}

				/* not operator */
				inline auto operator!(void) const noexcept -> bool {
					return _entity == nullptr;
				}


				// -- public accessors ----------------------------------------

				/* get name of entity */
				auto name(void) const noexcept -> xns::string_view {
					return _entity->d_name;
				}

				/* get path of entity */
				auto path(void) const -> xns::string requires (recursive == true) {
					//xns::string path{_container.top()._second};
					xns::string path{xns::get<xns::string>(_container.top())};
					path.append(SEPARATOR);
					#if defined(APPLE_OS)
						path.append(_entity->d_name, _entity->d_namlen);
					#else
						path.append(_entity->d_name);
					#endif

					return path;
				}

				/* get path of entity */
				auto path(void) const -> xns::string requires (recursive == false) {
					//xns::string path{_container._second};
					xns::string path{xns::get<xns::string>(_container)};
					path.append(SEPARATOR);
					#if defined(APPLE_OS)
						path.append(_entity->d_name, _entity->d_namlen);
					#else
						path.append(_entity->d_name);
				    #endif

					return path;
				}


				// -- public boolean methods ----------------------------------

				/* is hidden */
				inline auto is_hidden(void) const noexcept -> bool {
					return _entity->d_name[0] == POINT;
				}

				/* is unknown */
				inline auto is_unknown(void) const noexcept -> bool {
					return _entity->d_type == DT_UNKNOWN;
				}

				/* is directory */
				inline auto is_directory(void) const noexcept -> bool {
					return _entity->d_type == DT_DIR;
				}

				/* is regular */
				inline auto is_regular(void) const noexcept -> bool {
					return _entity->d_type == DT_REG;
				}

				/* is symbolic link */
				inline auto is_symlink(void) const noexcept -> bool {
					return _entity->d_type == DT_LNK;
				}

				/* is block */
				inline auto is_block(void) const noexcept -> bool {
					return _entity->d_type == DT_BLK;
				}

				/* is character */
				inline auto is_character(void) const noexcept -> bool {
					return _entity->d_type == DT_CHR;
				}

				/* is fifo */
				inline auto is_fifo(void) const noexcept -> bool {
					return _entity->d_type == DT_FIFO;
				}

				/* is socket */
				inline auto is_socket(void) const noexcept -> bool {
					return _entity->d_type == DT_SOCK;
				}



			private:

				// -- private utility methods ---------------------------------

				/* check '.' and '..' directories */
				inline auto skip(void) const noexcept -> bool {
					// branchless ternary
					return _entity->d_name[0] == POINT  ?
						   _entity->d_name[1] == '\0' ? true :
						   _entity->d_name[1] == POINT  ?
						   _entity->d_name[2] == '\0' ? true : false : false : false;
				}


				// -- private members -----------------------------------------

				/* directory container */
				container _container;

				/* directory entity */
				entity_ptr _entity;

		};


		// -- iterator types --------------------------------------------------

		/* linear iterator type */
		using iterator = directory_iterator<false>;

		/* recursive iterator type */
		using recursive_iterator = directory_iterator<true>;







	}

}




//enum Typeindex {
//	T_UNK, T_FIF, T_CHR,
//	T_DIR, T_BLK, T_REG,
//	T_LNK, T_SOC, T_WHT,
//	TYPE_N
//};
//
//struct Typentity {
//	const char*	_label;
//	xns::size_t		_size;
//	Typeindex	_index;
//};
//
//enum : bool {
//	NOERR,
//	ERROR
//};
//
//
//
//
//		enum Err: bool { NOERR, ERROR };
//
//	private:
//
//#define S_SLASH	"\x2F"
//#define C_SLASH	'\x2F'
//#define S_BACK	".."
//
//		// -- P R I V A T E  M E M B E R S ------------------------------------
//
//		String _absolute;
//		Dir* _directory;
//		List<DirEntity> _content[TYPE_N];
//		bool _isopen;
//
//	void reset(void);
//	void deallocation(void);
//	void clearDirectory(void);
//	void removeDots(void);
//
//	static Err makeDirectory(const String& path);
//	Directory& operator=(const Directory& other);
//
//
//	static void simplify(String& path);
//	static void makeAbsolute(String& path);
//	static bool isSlashTerminated(const String& path);
//	static bool isRelative(const String& path);
//
//	static Typeindex getTypentity(const xns::s32 type);
//
//	const char* getDirectoryPath(void) const;
//
//	//Err openDir(const char* path);
//	Err openDir(const String& path);
//	Err createDirectory(const String& path);
//
//	bool isOpen(void) const;
//
//	// excludeRegister()
//
//	void getDirectoryContent(void);
//
//	xns::u32 getFilesNumber(void) const;
//
//	const char* getNextFilePath(void) const;
//
//	void print(const Typeindex type) const;
//
//	const List<DirEntity>& getContent(const Typeindex type) const;
//
//};






// #ifdef _DARWIN_FEATURE_64_BIT_INODE
//
// DT_UNKNOWN	0
// Only some filesystems have full support to return the type of the file,
// others might always return this value.
// DT_FIFO		1 Named pipe
// DT_CHR		2 Character device
// DT_DIR		4 Directory
// DT_BLK		6 Block device
// DT_REG		8 Regular file
// DT_LNK		10 Symbolic link
// DT_SOCK		12 UNIX domain socket
// DT_WHT		14 Whiteout inode


// st_dev;			/* ID of device containing file */
// st_ino;			/* Inode number */
// st_mode;			/* File type and mode */
// st_nlink;		/* Number of hard links */
// st_uid;			/* User ID of owner */
// st_gid;			/* Group ID of owner */
// st_rdev;			/* Device ID (if special file) */
// st_size;			/* Total size, in bytes */
// st_blksize;		/* Block size for filesystem I/O */
// st_blocks;		/* Number of 512B blocks allocated */
// st_atim;			/* Time of last access */
// st_mtim;			/* Time of last modification */
// st_ctim;			/* Time of last status change */
#endif

		// -- D I R E C T O R Y  E N T R Y ------------------------------------

		//class directory_entry final {

		//	public:

		//		// -- public constructors -------------------------------------

		//		/* default constructor */
		//		directory_entry(void);

		//		/* member constructor */
		//		directory_entry(const xns::string& path) {
		//			stat(path.pointer(), &_stat);
		//		}

		//		/* copy constructor */
		//		directory_entry(const directory_entry& other)
		//		: _name{other._name}, _path{other._path}, _stat{other._stat} {
		//		}

		//		/* destructor */
		//		~directory_entry(void);


		//	private:

		//		// -- private types -------------------------------------------

		//		/* file stat */
		//		//using filestat   = struct stat;


		//		// -- private members -----------------------------------------

		//		/* name of entity */
		//		xns::string _name;

		//		/* full path of entity */
		//		xns::path<xns::string> _path;

		//		/* file stat */
		//		//filestat    _stat;

		//	public:

		//		// -- public accessors ----------------------------------------

		//		/* get name of entity */
		//		const xns::string& get_name(void) const;

		//		/* get full path of entity */
		//		const xns::path<xns::string>& get_path(void) const;

		//		/* get file size */
		//		xns::size_t get_size(void) const;


		//		// -- public boolean methods ----------------------------------

		//		/* is directory */
		//		bool is_directory(void) const;

		//		/* is regular */
		//		bool is_regular(void) const;

		//		/* is symbolic link */
		//		bool is_symlink(void) const;

		//		/* is block */
		//		bool is_block(void) const;

		//		/* is character */
		//		bool is_character(void) const;

		//		/* is fifo */
		//		bool is_fifo(void) const;

		//};
