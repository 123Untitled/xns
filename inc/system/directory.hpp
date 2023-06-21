#ifndef DIRECTORY_HEADER
#define DIRECTORY_HEADER

#include "string.hpp"
#include "types.hpp"
#include "path.hpp"

#include <dirent.h>
#include <sys/param.h>
#include <sys/stat.h>


//#include <cstdio>
//#include <string>
//#include <cstdint>
//#include <cstring>
//#include <iostream>
//#include <unistd.h>



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- F I L E  S Y S T E M ------------------------------------------------

	namespace filesystem {




		// -- D I R E C T O R Y  E N T R Y ------------------------------------

		class directory_entry final {

			public:

				// -- public constructors -------------------------------------

				/* default constructor */
				directory_entry(void);

				/* member constructor */
				directory_entry(const xns::string& path) {
					stat(path.pointer(), &_stat);
				}

				/* copy constructor */
				directory_entry(const directory_entry& other)
				: _name{other._name}, _path{other._path}, _stat{other._stat} {
				}

				/* destructor */
				~directory_entry(void);


			private:

				// -- private types -------------------------------------------

				/* file stat */
				using filestat   = struct stat;


				// -- private members -----------------------------------------

				/* name of entity */
				xns::string _name;

				/* full path of entity */
				xns::path<xns::string> _path;

				/* file stat */
				filestat    _stat;

			public:

				// -- public accessors ----------------------------------------

				/* get name of entity */
				const xns::string& get_name(void) const;

				/* get full path of entity */
				const xns::path<xns::string>& get_path(void) const;

				/* get file size */
				xns::size_t get_size(void) const;


				// -- public boolean methods ----------------------------------

				/* is directory */
				bool is_directory(void) const;

				/* is regular */
				bool is_regular(void) const;

				/* is symbolic link */
				bool is_symlink(void) const;

				/* is block */
				bool is_block(void) const;

				/* is character */
				bool is_character(void) const;

				/* is fifo */
				bool is_fifo(void) const;

		};


		// -- I T E R A T O R -------------------------------------------------

		template <bool recursive = false>
		class directory_iterator final {


			private:

				// -- private types -------------------------------------------

				/* directory type */
				using directory  = DIR;

				/* directory entry type */
				using dir_entity = struct dirent;


			public:

				// -- public constructors -------------------------------------

				/* deleted default constructor */
				directory_iterator(void) = delete;


				/* string constructor */
				directory_iterator(const xns::string& path)
				: _directory{nullptr}, _entity{nullptr}, _path{path} {

					_directory = opendir(_path.get().pointer());
					if (_directory == nullptr) {
						write(STDERR_FILENO, "Error: could not open directory\n", 32);
						return;
					}
					_entity = readdir(_directory);
				}

				/* destructor */
				~directory_iterator(void) {
					if (_directory != nullptr)
						closedir(_directory);
				}


				// -- public increment operators ------------------------------

				/* increment operator */
				directory_iterator& operator++(void) {
					// check if directory is open
					if (_directory != nullptr) {
						// get next entry
						_entity = readdir(_directory);
					} // return self reference
					return *this;
				}

				/* increment operator */
				directory_iterator& operator++(int) = delete;


				// -- public accessors operators ------------------------------

				/* dereference operator */
				directory_entry operator*(void) const {

					xns::filesystem::directory_entry entry{_path.get() + '/' + _entity->d_name};

					return entry;
				}


				// -- comparison operators ------------------------------------

				/* equality operator */
				bool operator==(const directory_iterator& other) const {
					return _entity == other._entity;
				}

				/* inequality operator */
				bool operator!=(const directory_iterator& other) const {
					return _entity != other._entity;
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


				// -- public boolean methods ----------------------------------

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



			private:


				/* directory */
				directory* _directory;

				/* directory entity */
				dir_entity* _entity;

				/* directory path */
				xns::path<xns::string> _path;


		};


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
