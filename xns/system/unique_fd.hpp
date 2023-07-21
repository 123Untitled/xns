#ifndef UNIQUE_HPP
#define UNIQUE_HPP

#include "types.hpp"
#include "allocator.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include <type_traits>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- U N I Q U E  F D  C L A S S -----------------------------------------

	class unique_fd final {

		public:

			// -- T Y P E S ---------------------------------------------------

			/* file descriptor type */
			using fd = pid_t;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			unique_fd(void);

			/* file descriptor constructor */
			unique_fd(const fd fd);

			/* deleted copy constructor */
			unique_fd(const unique_fd&) = delete;

			/* move constructor */
			unique_fd(unique_fd&& other) noexcept;

			/* destructor */
			~unique_fd(void);


			// -- O P E R A T O R S -------------------------------------------

			/* deleted copy assignment operator */
			unique_fd& operator=(const unique_fd&) = delete;

			/* move assignment operator */
			unique_fd& operator=(unique_fd&& other) noexcept;

			/* bool operator */
			explicit operator bool(void) const;

			/* bool not operator */
			bool operator!(void) const;


			// -- M E T H O D S -----------------------------------------------

			/* get file descriptor */
			fd get(void) const;

			/* duplicate */
			unique_fd duplicate(void) const;

			/* duplicate 2 */
			void duplicate(unique_fd& other) const;


			/* make fd */
			static unique_fd make_fd(const fd);


		private:

			// -- E N U M S --------------------------------------------------

			/* invalid file descriptor */
			enum : int  { NULLFD = -1 };


			// -- M E M B E R S -----------------------------------------------

			/* file descriptor */
			fd _fd;

	};



};

#endif

