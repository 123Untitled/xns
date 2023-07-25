#ifndef DEBUG_HEADER
#define DEBUG_HEADER

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>


#include "type_traits.hpp"
#include "types.hpp"
#include "macro.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- D E B U G -----------------------------------------------------------

	class debug {

		public:

			// -- public constructors -----------------------------------------

			/* non-instantiable class */
			NON_INSTANCIABLE(debug);


			static int _tty;

			static int initialize(const char* = nullptr);

			static void write(const void*, xns::size_t = 0);

			template <typename... A>
			static void print(const char* msg, A&&... args) {
				// exit if no message or tty not open
				if (!msg)     { return; }
				if (_tty < 0) { return; }

				// avoid format-security warning
				#pragma clang diagnostic push
				#pragma clang diagnostic ignored "-Wformat-security"
				// call fd printf with packed arguments
				dprintf(_tty, msg, xns::forward<A>(args)...);
				#pragma clang diagnostic pop
			}


	};

}

#endif // XF_DEBUG_HPP
