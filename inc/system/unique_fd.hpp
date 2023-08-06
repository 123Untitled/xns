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

	class unique_fd final {


		public:

			// -- public types ------------------------------------------------

			/* file descriptor type */
			using fd_type = int;

			/* self type */
			using self = unique_fd;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			unique_fd(void) noexcept;

			/* file descriptor constructor */
			explicit unique_fd(const fd_type fd) noexcept;

			/* variadic constructor */
			template <xns::is_string S, class... A>
			explicit unique_fd(const S& path, A&&... args) noexcept
			: _fd{::open(path.data(), args...)} {
			}

			/* non-copyable class */
			NON_COPYABLE(unique_fd);

			/* move constructor */
			unique_fd(self&& other) noexcept;

			/* destructor */
			~unique_fd(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* move assignment operator */
			self& operator=(unique_fd&& other) noexcept;


			// -- public boolean operators ------------------------------------

			/* boolean operator */
			explicit operator bool(void) const;

			/* not operator */
			bool operator!(void) const;


			// -- public accessors --------------------------------------------

			/* valid */
			bool valid(void) const noexcept;

			/* get file descriptor */
			fd_type get(void) const noexcept;


			// -- M E T H O D S -----------------------------------------------


			/* duplicate */
			unique_fd duplicate(void) const;

			/* duplicate 2 */
			void duplicate(self& other) const;



		private:

			// -- private enums -----------------------------------------------

			/* invalid file descriptor */
			enum : xns::s8  { NULLFD = -1 };


			// -- private members ---------------------------------------------

			/* file descriptor */
			fd_type _fd;

	};



};

#endif

