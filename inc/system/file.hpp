#ifndef FILE_HEADER
#define FILE_HEADER

#include "string.hpp"
#include "draw.hpp"
#include "unique_fd.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- F I L E  C L A S S --------------------------------------------------

	class file final {

		public:

			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			file(void);

			/* path constructor */
			file(const xns::cstring&);

			/* non-assignable class */
			NON_ASSIGNABLE(file);

			/* destructor */
			~file(void);


			void file_name(xns::cstring&& name);

			/* open file */
			void open(void);

			/* get file content */
			void content(void);


			/* get path */
			const xns::cstring& path(void) const;

		private:

			// -- A L I A S E S -----------------------------------------------

			using Stat = struct stat;


			// -- P R I V A T E  M E M B E R S --------------------------------

			xns::cstring _file;
			xns::cstring _path;
			xns::unique_fd     _fd;
			Stat             _data;
			bool             _state;

			void operator|(file);


	};

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
