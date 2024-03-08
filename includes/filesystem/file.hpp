#ifndef XNS_FILE_HEADER
#define XNS_FILE_HEADER

// local headers
#include "string.hpp"
#include "unique_descriptor.hpp"

// operating system headers
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- F I L E  C L A S S --------------------------------------------------

	template <decltype(sizeof(0)) S = 1024>
	class file final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::file<S>;

			/* size type */
			using size_type = decltype(S);

			/* signed type */
			using signed_type = xns::s64;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline file(void) noexcept
			: _descriptor{}, _buffer{}, _readed{0} {}

			/* variadic constructor */
			template <typename... A>
			inline file(const xns::string& path, A&&... args) noexcept
			: _descriptor{::open(path.data(), args...)},
			  _buffer{}, _readed{0} {}

			/* move constructor */
			inline file(self&& other) noexcept
			: unique_descriptor{xns::move(other)}, _buffer{}, _readed{0} {}

			/* non-copyable class */
			non_copyable(file);

			/* destructor */
			~file(void) noexcept = default;


			// -- public accessors --------------------------------------------

			/* is open */
			inline auto is_open(void) const noexcept -> bool {
				return _descriptor.valid();
			}


			/* get file content */
			inline auto content(void) const -> xns::string {


				// check if file is open
				if (!is_open()) {
					return {};
				}

				// get file size
				struct ::stat stat;

				if (::fstat(_descriptor, &stat) < 0) {
					return {};
				}

				// allocate buffer
				xns::string content{};

				content.resize(static_cast<size_type>(stat.st_size));

				// read file
				if (::read(_descriptor,
							content.data(),
							static_cast<size_type>(stat.st_size)) == -1) {
					return {};
				}

				// return content
				return content;
			}


			// -- public methods ----------------------------------------------
			
			/* read */
			inline auto read(void) noexcept -> size_type {
				// read descriptor
				signed_type readed = static_cast<signed_type>(::read(_descriptor, _buffer, S));
				// assign readed bytes
				_readed = static_cast<size_type>(readed > 0 ? readed : 0);
				// return readed bytes
				return _readed;
			}

			/* readed */
			inline auto readed(void) const noexcept -> size_type {
				// return readed bytes
				return _readed;
			}



			// -- public subscript operators ----------------------------------

			/* subscript operator */
			template <typename T>
			inline auto operator[](const T& index) noexcept -> char& {
				// assertion
				static_assert(xns::is_integral<T>, "index must be integral");
				// return buffer
				return _buffer[index];
			}



		private:

			// -- private members ---------------------------------------------

			/* descriptor */
			xns::unique_descriptor _descriptor;

			/* buffer */
			char _buffer[S];

			/* readed bytes */
			size_type _readed;

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
