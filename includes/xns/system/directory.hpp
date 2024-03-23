/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_DIRECTORY_HEADER
#define XNS_DIRECTORY_HEADER

// local headers
#include "xns/config/os.hpp"

#include "xns/type_traits/other/string_literal.hpp"
#include "xns/type_traits/types.hpp"

#include "xns/string/string.hpp"

#include "xns/containers/stack.hpp"
#include "xns/containers/pair.hpp"

#include "xns/system/unique_directory.hpp"
#include "xns/system/path.hpp"



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- F I L E  S Y S T E M ------------------------------------------------

	namespace filesystem {


		// -- D I R E C T O R Y  I T E R A T O R ------------------------------

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
				using self = xns::filesystem::directory_iterator<recursive>;


				// -- public constructors -------------------------------------

				/* deleted default constructor */
				directory_iterator(void) = delete;

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
				auto operator++(int) -> self = delete;



				// -- comparison operators ------------------------------------

				/* equality operator */
				inline auto operator==(const self& other) const noexcept -> bool {
					// compare inodes of entities
					#if defined(XNS_BSD) || defined(XNS_APPLE)
						return  _entity
							&&  other._entity
							&& (_entity->d_ino == other._entity->d_ino);
					#elif defined(XNS_LINUX)
						return  _entity
							&&  other._entity
							&& (_entity->d_fileno == other._entity->d_fileno);
					#endif
				}

				/* inequality operator */
				inline auto operator!=(const self& other) const noexcept -> bool {
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
				inline explicit operator bool(void) const noexcept {
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








//Directory::Directory(void)
//: _absolute{}, _directory{nullptr}, _content{}, _isopen{false} {
//	_absolute.reserve(MAXPATHLEN);
//}
//
///* copy constructor */
//Directory::Directory(const Directory& other)
//: Directory{} {
//}
//
///* copy assignment operator */
//Directory& Directory::operator=(const Directory& other)
//{
//	return *this;
//}
//
//Directory::~Directory(void) {
//	deallocation();
//}
//
//bool Directory::isRelative(const String& path) {
//	return (path.front() != C_SLASH ? true : false);
//}
//
//bool Directory::isSlashTerminated(const String& path) {
//	return (path.back() == C_SLASH ? true : false);
//}
//
//void Directory::makeAbsolute(String& path) {
//	static char buff[MAXPATHLEN];
//
//	if (isRelative(path) && getcwd(buff, MAXPATHLEN) != nullptr)
//		path = String{buff} + String{S_SLASH} + path;
//}
//
//
////std::vector<std::list>
//
//
//
//
//
//
//Directory::Err Directory::openDir(const String& path) {
//	// check null pointer
//	if (path.length()) {
//		// reset previous opening
//		reset();
//		// assign path to private member
//		_absolute = path;
//		// make absolute path if relative
//		makeAbsolute(_absolute);
//		// try to open directory
//		if ((_directory = opendir(_absolute.c_str()))) {
//			// set flag ok to search in directory
//			_isopen = true;
//			// clean path
//			simplify(_absolute);
//			// get folder content
//			getDirectoryContent();
//			// return success
//			return (NOERR);
//		} // else return error
//	} return (ERROR);
//}
//

//void Directory::getDirectoryContent(void) {
//
//	const Dirent* file = nullptr;
//	if (_isopen) {
//		while ((file = readdir(_directory))) {
//			Typeindex i = getTypentity(file->d_type);
//
//			_content[i].push_back(DirEntity{_absolute, file});
//		} rewinddir(_directory);
//		removeDots();
//	}
//}
//
//const List<DirEntity>& Directory::getContent(const Typeindex type) const {
//	return (_content[type]);
//}
//
//unsigned Directory::getFilesNumber(void) const {
//	unsigned long size = 0;
//	for (unsigned long x = 0; x < TYPE_N; x++)
//		size += _content[x].size();
//	return (size);
//}
//
//
//
//const char* _labels[TYPE_N] = {
//	"unknown",
//	"pipe",
//	"character",
//	"directory",
//	"block",
//	"regular file",
//	"symbolic link",
//	"socket",
//	"whiteout"
//};
//
//void Directory::print(const Typeindex type) const {
//	auto ite = _content[type].begin();
//	while (ite != _content[type].end()) {
//		std::cout << _labels[type] << " - " << ite->getName() << std::endl;
//		ite++;
//	}
//}
//
//const char* Directory::getNextFilePath(void) const {
//	/*
//	static auto iterator = _content.begin();
//	if (iterator != _content.end())
//		return ((iterator++)->_name.c_str());
//	iterator = _content.begin();
//	*/
//	return (nullptr);
//}
//
//
//
//void tt() {
//	Typentity types[TYPE_N];
//	for (unsigned long x = 0; x < TYPE_N; x++) {
//		types[x]._label = _labels[x];
//		types[x]._size = sizeof(_labels[x]);
//		types[x]._index = static_cast<Typeindex>(x);
//	}
//
//	static Typentity* _converter[DT_WHT + 1] {
//		&types[T_UNK], &types[T_FIF], &types[T_CHR],
//		nullptr, &types[T_DIR], nullptr,
//		&types[T_BLK], nullptr, &types[T_REG],
//		nullptr, &types[T_LNK], nullptr,
//		&types[T_SOC], nullptr, &types[T_WHT]
//	};
//}
//
//Typeindex Directory::getTypentity(const int type) {
//	switch (type) {
//		case DT_REG:		return (T_REG);
//		case DT_DIR:		return (T_DIR);
//		case DT_LNK:		return (T_LNK);
//		case DT_CHR:		return (T_CHR);
//		case DT_BLK:		return (T_BLK);
//		case DT_WHT:		return (T_WHT);
//		case DT_SOCK:		return (T_UNK);
//		case DT_FIFO:		return (T_FIF);
//		default:			return (T_UNK);
//	} return (T_UNK);
//}
//
//
//// DirEntity default constructor
//DirEntity::DirEntity(void)
//: _name{}, _path{}, _dirent{}, _stat{} {
//	// structures manual initialization
//	std::memset(&_dirent,	0, sizeof(Dirent));
//	std::memset(&_stat,		0, sizeof(Stat));
//}
//
//DirEntity::DirEntity(const String& path, const Dirent* dirent)
//// initialize name and full path
//: _name{dirent->d_name, strlen(dirent->d_name)}, _path{path + _name}, _dirent{}, _stat{}  {
//	// memory copy 'Dirent' structure
//	std::memcpy(&_dirent, dirent, sizeof(Dirent));
//	// get stat data about entity
//	stat(_path.c_str(), &_stat);
//}
//
//DirEntity::~DirEntity(void) {
//	// DirEntity destructor
//}
//
//const String& DirEntity::getName(void) const {
//	return (_name);
//}
//
//const String& DirEntity::getPath(void) const {
//	return (_path);
//}
//
//
//// unix NAME_MAX
//// bsd MAXNAMLEN
//// stdio macro FILENAME_MAX
//
//String DirEntity::getLinkPath(const String& link) {
//	char buff[MAXNAMLEN];
//	int size = readlink(link.c_str(), buff, MAXNAMLEN);
//	if (size == -1)
//		return (perror("symlink"), String());
//	return (String(buff, size));
//}
//
//
//bool DirEntity::makeLink(const String& source, const String& link) {
//	return (symlink(source.c_str(), link.c_str()) == -1 ? ERROR : NOERR);
//}





