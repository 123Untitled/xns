#ifndef XNS_UNIQUE_DIRECTORY_HPP
#define XNS_UNIQUE_DIRECTORY_HPP

// local headers
#include "os.hpp"
#include "macros.hpp"
#include "string.hpp"
#include "unique_descriptor.hpp"

// macos headers
#if defined(XNS_APPLE)
	#include <sys/dir.h>
// linux headers
#elif defined(XNS_LINUX)
	#include <dirent.h>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- U N I Q U E  D I R E C T O R Y --------------------------------------

	class unique_directory {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::unique_directory;

			/* directory type */
			using directory = DIR;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline unique_directory(void) noexcept
			: _directory{nullptr} {}

			/* non-copyable class */
			NON_COPYABLE(unique_directory);

			/* string constructor */
			template <typename T> requires xns::is_string<T>
			inline explicit unique_directory(const T& path) noexcept
			: _directory{::opendir(path.data())} {
			}

			/* unique_descriptor constructor */
			inline explicit unique_directory(const xns::unique_descriptor& descriptor) noexcept
			: _directory{::fdopendir(descriptor)} {
			}

			/* pointer constructor */
			inline explicit unique_directory(const char* path) noexcept
			: _directory{::opendir(path)} {
			}

			/* move constructor */
			inline unique_directory(unique_directory&& other) noexcept
			: _directory{other._directory} {
				// invalidate other
				other._directory = nullptr;
			}

			/* destructor */
			inline ~unique_directory(void) noexcept {
				// check if directory is open
				if (_directory == nullptr) { return; }
				// close directory
				::closedir(_directory);
			}


			// -- public assignment operators ---------------------------------

			/* move assignment operator */
			inline auto operator=(unique_directory&& other) noexcept -> self& {
				// check for self-assignment
				if (this == &other)
					return *this;
				// close directory
				if (_directory != nullptr) ::closedir(_directory);
				// move directory
				_directory = other._directory;
				// invalidate other
				other._directory = nullptr;
				// return self-reference
				return *this;
			}


			// -- public conversion operators ---------------------------------

			/* pointer conversion operator */
			inline operator directory*(void) const noexcept {
				// return pointer
				return _directory;
			}


			// -- public accessors --------------------------------------------

			/* get directory */
			inline auto get(void) const noexcept -> directory* {
				// return pointer
				return _directory;
			}

			/* is open */
			inline auto is_open(void) const noexcept -> bool {
				// return pointer validity
				return _directory != nullptr;
			}

			/* is closed */
			inline auto is_closed(void) const noexcept -> bool {
				// return pointer invalidity
				return _directory == nullptr;
			}


		private:

			// -- private members ---------------------------------------------

			/* directory pointer */
			directory* _directory;

	}; // class unique_directory

} // namespace xns

#endif // UNIQUE_DIRECTORY_HPP
