#ifndef UNIQUE_HPP
#define UNIQUE_HPP

// local headers
#include "types.hpp"
#include "allocator.hpp"
#include "macro.hpp"
#include "string.hpp"

// operating system headers
#include <fcntl.h>
#include <unistd.h>

// c++ standard headers
#include <iostream>
#include <type_traits>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- U N I Q U E  F D  C L A S S -----------------------------------------

	//class unique_fd final {


	//	public:

	//		// -- public types ------------------------------------------------

	//		/* file descriptor type */
	//		using fd_type = int;

	//		/* self type */
	//		using self = unique_fd;


	//		// -- public lifecycle --------------------------------------------

	//		/* default constructor */
	//		unique_fd(void) noexcept;

	//		/* file descriptor constructor */
	//		explicit unique_fd(const fd_type fd) noexcept;

	//		/* variadic constructor */
	//		template <xns::is_string S, class... A>
	//		explicit unique_fd(const S& path, A&&... args) noexcept
	//		: _fd{::open(path.data(), args...)} {
	//		}

	//		/* non-copyable class */
	//		NON_COPYABLE(unique_fd);

	//		/* move constructor */
	//		unique_fd(self&& other) noexcept;

	//		/* destructor */
	//		~unique_fd(void) noexcept;


	//		// -- public assignment operators ---------------------------------

	//		/* move assignment operator */
	//		self& operator=(unique_fd&& other) noexcept;


	//		// -- public boolean operators ------------------------------------

	//		/* boolean operator */
	//		explicit operator bool(void) const;

	//		/* not operator */
	//		bool operator!(void) const;


	//		// -- public accessors --------------------------------------------

	//		/* valid */
	//		bool valid(void) const noexcept;

	//		/* get file descriptor */
	//		fd_type get(void) const noexcept;


	//		// -- M E T H O D S -----------------------------------------------


	//		/* duplicate */
	//		unique_fd duplicate(void) const;

	//		/* duplicate 2 */
	//		void duplicate(self& other) const;



	//	private:

	//		// -- private enums -----------------------------------------------

	//		/* invalid file descriptor */
	//		enum : xns::s8  { NULLFD = -1 };


	//		// -- private members ---------------------------------------------

	//		/* file descriptor */
	//		fd_type _fd;

	//};


	// -- T R U S T  T A G  S T R U C T ---------------------------------------

	struct trust {

		/* trust constructor */
		explicit constexpr trust(void) noexcept = default;

	};



	// -- U N I Q U E  D E S C R I P T O R  -----------------------------------

	/* unique descriptor */
	class unique_descriptor {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = unique_descriptor;

			/* descriptor type */
			using descriptor = int;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline unique_descriptor(void) noexcept
			: _descriptor{NULL_DESCRIPTOR} {}

			/* descriptor constructor */
			inline unique_descriptor(const descriptor& descriptor) noexcept
			: _descriptor{check_descriptor(descriptor)} {
					std::cout << "checking descriptor: " << _descriptor << std::endl;
			}

			/* non-copyable class */
			NON_COPYABLE(unique_descriptor);

			/* move constructor */
			inline unique_descriptor(self&& other) noexcept
			: _descriptor{other._descriptor} {
				// invalidate other
				other._descriptor = NULL_DESCRIPTOR;
			}

			/* destructor */
			inline ~unique_descriptor(void) noexcept {
				// close descriptor
				close_descriptor();
			}


			// -- public assignment operators ---------------------------------

			/* move assignment operator */
			inline auto operator=(self&& other) noexcept -> self& {
				// check for self assignment
				if (this != &other) {
					// close descriptor
					close_descriptor();
					// set descriptor
					_descriptor = other._descriptor;
					// invalidate other
					other._descriptor = NULL_DESCRIPTOR;
				} // return self reference
				return *this;
			}

			/* descriptor assignment operator */
			inline auto operator=(const descriptor& descriptor) noexcept -> void {
				// set descriptor
				_descriptor = check_descriptor(descriptor);
			}


			// -- public boolean operators ------------------------------------

			/* boolean operator */
			inline explicit operator bool(void) const noexcept {
				// return descriptor validity
				return _descriptor != NULL_DESCRIPTOR;
			}

			/* not operator */
			inline bool operator!(void) const noexcept {
				// return descriptor invalidity
				return _descriptor == NULL_DESCRIPTOR;
			}


			// -- public conversion operators -----------------------------

			/* descriptor conversion operator */
			inline explicit operator descriptor(void) const noexcept {
				// return descriptor
				return _descriptor;
			}


			// -- public comparison operators -----------------------------

			/* equality operator */
			inline auto operator==(const self& other) const noexcept -> bool {
				// return descriptor equality
				return _descriptor == other._descriptor;
			}

			/* inequality operator */
			inline auto operator!=(const self& other) const noexcept -> bool {
				// return descriptor inequality
				return _descriptor != other._descriptor;
			}


			// -- public accessors ----------------------------------------

			/* is valid */
			inline auto valid(void) const noexcept -> bool {
				// return descriptor validity
				return _descriptor != NULL_DESCRIPTOR;
			}

			/* is invalid */
			inline auto invalid(void) const noexcept -> bool {
				// return descriptor invalidity
				return _descriptor == NULL_DESCRIPTOR;
			}

			/* get descriptor */
			inline auto get(void) const noexcept -> const descriptor& {
				// return descriptor
				return _descriptor;
			}


			// -- public modifiers ----------------------------------------

			/* reset descriptor */
			inline auto reset(void) noexcept -> void {
				// close descriptor
				close_descriptor();
				// invalidate descriptor
				_descriptor = NULL_DESCRIPTOR;
			}

			/* set descriptor */
			inline auto set(const descriptor& descriptor) noexcept -> void {
				// close descriptor
				close_descriptor();
				// set descriptor
				_descriptor = descriptor;
			}


		private:

			// -- private lifecycle -------------------------------------------

			/* private trusted constructor */
			inline unique_descriptor(const trust, const descriptor& descriptor) noexcept
			: _descriptor{descriptor} {}


			// -- private methods ---------------------------------------------

			/* close descriptor */
			inline auto close_descriptor(void) noexcept -> void {
				// check for valid descriptor
				if (_descriptor != NULL_DESCRIPTOR) {
					// close descriptor
					if (::close(_descriptor) == -1) {
						// error
					}
				}
			}

			/* check descriptor */
			inline auto check_descriptor(const descriptor& descriptor)
				noexcept -> unique_descriptor::descriptor {
				// check if descriptor is valid
				return (::fcntl(descriptor, F_GETFD) != -1 || errno != EBADF)
					? descriptor : NULL_DESCRIPTOR;
			}


			// -- private enums -----------------------------------------------

			/* descriptor type */
			enum { NULL_DESCRIPTOR = -1 };


			// -- private members ---------------------------------------------

			/* descriptor */
			descriptor _descriptor;

	};




};

#endif

