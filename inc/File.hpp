#ifndef _FILE_HEADER_
#define _FILE_HEADER_


#include "Str.hpp"
#include "Draw.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


class File {

private:
	typedef struct stat Stat;
	#define FILE_BUFFER_SIZE 64

	String		_file;
	String		_path;
	int     _fd;
	Stat	_data;

	// deleted method
	File(const File& copy) = delete;
	File(const File&& move) = delete;

public:
	// constructor and destructor
	File(void);
	File(const String& name);
	~File(void);

	void	setFileName(String&& name);
	int		openFile(void);
	int		catchFile(void);
	void	print(void);

	// getter
	const String& getPath(void) const;

};


/*
dev_t    st_dev;				// device inode resides on
ino_t    st_ino;				// inode's number
mode_t   st_mode;				// inode protection mode
nlink_t  st_nlink;				// number of hard links to the file
uid_t    st_uid;				// user-id of owner
gid_t    st_gid;				// group-id of owner
dev_t    st_rdev;				// device type, for special file inode
struct timespec st_atimespec;	// time of last access
struct timespec st_mtimespec;	// time of last data modification
struct timespec st_ctimespec;	// time of last file status change
off_t    st_size;    file size, in bytes
quad_t   st_blocks;  blocks allocated for file
u_long   st_blksize; optimal file sys I/O ops blocksize
u_long   st_flags;   user defined flags for file
u_long   st_gen;     file generation number
*/

#endif
