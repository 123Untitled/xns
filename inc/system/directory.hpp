#ifndef DIRECTORY_HEADER
#define DIRECTORY_HEADER

#include <dirent.h>
#include <cstdio>
#include <string>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <list>
#include <unistd.h>
#include <sys/param.h>
#include <sys/stat.h>

#include "types.hpp"



// alias types
template<typename T>
using List		= std::list<T>;
using String	= std::string;
using Stat		= struct stat;
using Dirent	= struct dirent;
using Dir		= DIR;

class DirEntity final {
	private:
	String		_name;
	String		_path;
	Dirent		_dirent;
	Stat		_stat;
	public:
	const String& getName(void) const;
	const String& getPath(void) const;

	static String getLinkPath(const String& link);

	static bool makeLink(const String& source, const String& link);

	DirEntity(const String& path, const Dirent* entity);
	DirEntity(void);
	~DirEntity(void);
};


enum Typeindex {
	T_UNK, T_FIF, T_CHR,
	T_DIR, T_BLK, T_REG,
	T_LNK, T_SOC, T_WHT,
	TYPE_N
};

struct Typentity {
	const char*	_label;
	UInt64		_size;
	Typeindex	_index;
};

enum : bool {
	NOERR,
	ERROR
};

// -- D I R E C T O R Y  C L A S S --------------------------------------------

class Directory final {

	public:

		// -- C O N S T R U C T O R S -----------------------------------------

		/* default constructor */
		Directory(void);

		/* copy constructor */
		Directory(const Directory& other);

		/* destructor */
		~Directory(void);


		enum Err: bool { NOERR, ERROR };

	private:

#define S_SLASH	"\x2F"
#define C_SLASH	'\x2F'
#define S_BACK	".."

		// -- P R I V A T E  M E M B E R S ------------------------------------

		String _absolute;
		Dir* _directory;
		List<DirEntity> _content[TYPE_N];
		bool _isopen;

	void reset(void);
	void deallocation(void);
	void clearDirectory(void);
	void removeDots(void);

	static Err makeDirectory(const String& path);
	Directory& operator=(const Directory& other);


	static void simplify(String& path);
	static void makeAbsolute(String& path);
	static bool isSlashTerminated(const String& path);
	static bool isRelative(const String& path);

	static Typeindex getTypentity(const SInt32 type);

	const char* getDirectoryPath(void) const;

	//Err openDir(const char* path);
	Err openDir(const String& path);
	Err createDirectory(const String& path);

	bool isOpen(void) const;

	// excludeRegister()

	void getDirectoryContent(void);

	UInt32 getFilesNumber(void) const;

	const char* getNextFilePath(void) const;

	void print(const Typeindex type) const;

	const List<DirEntity>& getContent(const Typeindex type) const;

};






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
