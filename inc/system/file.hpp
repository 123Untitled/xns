#ifndef FILE_HEADER
#define FILE_HEADER

// local headers
#include "string.hpp"
#include "draw.hpp"
#include "unique_descriptor.hpp"

// operating system headers
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- F I L E  C L A S S --------------------------------------------------

	class file final : public xns::unique_descriptor {


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline file(void) noexcept
			: unique_descriptor{} {}

			/* variadic constructor */
			template <typename... A>
			inline file(const xns::string& path, A&&... args) noexcept
			: unique_descriptor{xns::trust{}, ::open(path.data(), args...)} {}

			/* move constructor */
			inline file(xns::file&& other) noexcept
			: unique_descriptor{xns::move(other)} {}

			/* non-assignable class */
			NON_COPYABLE(file);

			/* destructor */
			inline ~file(void) noexcept {
				// code here...
			}




			/* get file content */
			void content(void);


		private:



			// -- private members ---------------------------------------------




	};

}


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
