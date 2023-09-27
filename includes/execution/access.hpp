#ifndef ACCESS_HPP
#define ACCESS_HPP

// xns headers
#include "environment.hpp"
#include "string.hpp"

// operating system headers
#include <unistd.h>



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A C C E S S ---------------------------------------------------------

	class access final {


		public:

			// -- public static methods ---------------------------------------

			/* check execution access */
			static bool x_ok(const xns::string&) noexcept;

			/* check read access */
			static bool r_ok(const xns::string&) noexcept;

			/* check write access */
			static bool w_ok(const xns::string&) noexcept;

			/* check existence */
			static bool f_ok(const xns::string&) noexcept;


			/* get execution access */
			static bool sys_x_ok(xns::string&);


			// -- public constructors -----------------------------------------

			/* default constructor */
			access(void) noexcept;

			/* copy constructor */
			access(const access&) noexcept;

			/* move constructor */
			access(access&&) noexcept;

			/* destructor */
			~access(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			access& operator=(const access&) noexcept;

			/* move assignment operator */
			access& operator=(access&&) noexcept;


		private:

			// -- private members ---------------------------------------------

	};

}

#endif
