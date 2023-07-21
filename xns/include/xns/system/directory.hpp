#ifndef DIRECTORY_HEADER
#define DIRECTORY_HEADER

// local headers
#include "string_literal.hpp"
#include "string.hpp"
#include "types.hpp"
#include "path.hpp"
#include "stack.hpp"
#include "pair.hpp"
#include "os.hpp"

// macos headers
#if defined(APPLE_OS)
	#include <sys/dir.h>
// linux headers
#elif defined(LINUX_OS)
	#include <dirent.h>
#endif



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- F I L E  S Y S T E M ------------------------------------------------

	namespace filesystem {




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


		// -- I T E R A T O R -------------------------------------------------

		template <bool recursive>
		class directory_iterator final {


			private:

				// -- private types -------------------------------------------

				/* container type */
				using container = xns::conditional<recursive,
												   xns::stack<xns::pair<DIR*, xns::string>>,
												   xns::pair<DIR*, xns::string>>;

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
				directory_iterator(xns::null)
				: _container{}, _entity{nullptr} {}

				/* path constructor (non-recursive) */
				directory_iterator(const xns::string& path) requires (recursive == false)
				: _container{}, _entity{nullptr} {
					// check path validity
					if (path.empty() == true) { return; }
					// open directory and set pair
					_container = xns::pair{::opendir(path.data()), path};
					// check opening failure
					if (_container._first == nullptr) {
						write(STDERR_FILENO, "Error: could not open directory\n", 32);
						return;
					} // get first entry
					operator++();
				}

				/* path constructor (recursive) */
				directory_iterator(const xns::string& path) requires (recursive == true)
				: _container{}, _entity{nullptr} {

					DIR* dir = ::opendir(path.data());
					// check opening failure
					if (dir == nullptr) {
						write(STDERR_FILENO, "Error: could not open directory\n", 32);
						return;
					}
					// open directory
					_container.push(xns::pair{dir, path});
					operator++();
				}

				/* non-assignable class */
				NON_ASSIGNABLE(directory_iterator);

				/* destructor */
				~directory_iterator(void) {

					if constexpr (recursive == false) {
						// close directory
						if (_container._first != nullptr) {
							::closedir(_container._first);
						}
					}
					else if constexpr (recursive == true) {
						// close all directories
						while (_container.empty() == false) {
							::closedir(_container.top()._first);
							_container.pop();
						}
					}
				}

				///* destructor (non-recursive) */
				//~directory_iterator(void) requires (recursive == false) {
				//	// close directory
				//	if (_container._first != nullptr) {
				//		::closedir(_container._first);
				//	}
				//}

				///* destructor (recursive) */
				//~directory_iterator(void) requires (recursive == true) {
				//	// close all directories
				//	while (_container.empty() == false) {
				//		::closedir(_container.top()._first);
				//		_container.pop();
				//	}
				//}


				// -- public increment operators ------------------------------

				/* pre-increment operator (non-recursive) */
				directory_iterator& operator++(void) requires (recursive == false) {
					// get next entry
					while ((_entity = ::readdir(_container._first)) != nullptr) {
						// check for directory '.' or '..'
						if (_entity->d_type == DT_DIR
							&& skip() == true) { continue; }
						// exit loop
						break;
					}
					return *this;
				}


				/* pre-increment operator (recursive) */
				directory_iterator& operator++(void) requires (recursive == true) {

					while (_container.empty() == false) {

						// get next entry
						_entity = ::readdir(_container.top()._first);

						// check for end of directory
						if (_entity == nullptr) {
							// close directory
							::closedir(_container.top()._first);
							_container.pop();
							continue;
						}

						// check for directory
						if (_entity->d_type == DT_DIR) {

							// skip '.' and '..' directories
							if (skip() == true) { continue; }

							xns::string path{_container.top()._second};
							path.append(SEPARATOR);
							#if defined(APPLE_OS)
								path.append(_entity->d_name, _entity->d_namlen);
						    #else
								path.append(_entity->d_name);
							#endif

							DIR* dir = ::opendir(path.data());

							// check opening failure (need to set errno like status)
							if (dir == nullptr) { break; }

							_container.push(xns::pair{dir, xns::move(path)});
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
				bool operator==(const directory_iterator& other) const {
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
				bool operator!=(const directory_iterator& other) const {
					return operator==(other) == false;
				}

				/* null pointer equality operator */
				bool operator==(xns::null) const {
					return _entity == nullptr;
				}

				/* null pointer inequality operator */
				bool operator!=(xns::null) const {
					return _entity != nullptr;
				}


				// -- public boolean operators --------------------------------

				/* boolean operator */
				operator bool(void) const {
					return _entity != nullptr;
				}

				/* not operator */
				bool operator!(void) const {
					return _entity == nullptr;
				}


				// -- public accessors ----------------------------------------

				/* get name of entity */
				xns::string_view name(void) const {
					return _entity->d_name;
				}

				/* get path of entity */
				xns::string path(void) const requires (recursive == true) {
					xns::string path{_container.top()._second};
					path.append(SEPARATOR);
					#if defined(APPLE_OS)
						path.append(_entity->d_name, _entity->d_namlen);
					#else
						path.append(_entity->d_name);
					#endif

					return path;
				}

				/* get path of entity */
				xns::string path(void) const requires (recursive == false) {
					xns::string path{_container._second};
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
				bool is_hidden(void) const {
					return _entity->d_name[0] == POINT;
				}

				/* is unknown */
				bool is_unknown(void) const {
					return _entity->d_type == DT_UNKNOWN;
				}

				/* is directory */
				bool is_directory(void) const {
					return _entity->d_type == DT_DIR;
				}

				/* is regular */
				bool is_regular(void) const {
					return _entity->d_type == DT_REG;
				}

				/* is symbolic link */
				bool is_symlink(void) const {
					return _entity->d_type == DT_LNK;
				}

				/* is block */
				bool is_block(void) const {
					return _entity->d_type == DT_BLK;
				}

				/* is character */
				bool is_character(void) const {
					return _entity->d_type == DT_CHR;
				}

				/* is fifo */
				bool is_fifo(void) const {
					return _entity->d_type == DT_FIFO;
				}

				/* is socket */
				bool is_socket(void) const {
					return _entity->d_type == DT_SOCK;
				}



			private:

				// -- private utility methods ---------------------------------

				/* check '.' and '..' directories */
				inline bool skip(void) const {
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
