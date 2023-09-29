#ifndef XNS_DEBUG_HEADER
#define XNS_DEBUG_HEADER

// local headers
#include "types.hpp"
#include "macros.hpp"
#include "unique_descriptor.hpp"

// c++ standard headers
#include <iostream>

// operating system headers
#include <fcntl.h>
#include <unistd.h>


#include <cstdio>
#include <cstring>




// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// command: echo $(tty) | nc -U ./xns_debug.sock

	// -- D E B U G -----------------------------------------------------------

	class debug {

		public:

			// -- private lifecycle -------------------------------------------

			/* deleted default constructor */
			debug(void) = delete;

			/* non-assignable class */
			NON_ASSIGNABLE(debug);

			/* destructor */
			~debug(void) = default;


			//static xns::unique_fd _tty;

			//static xns::unique_fd initialize(void) noexcept;


			template <typename... A>
			static void print(const char* msg, A&&... args) {
				// exit if no message or tty not open
				//if (!msg)     { return; }
				//if (_tty.valid() == false) { return; }

				//// avoid format-security warning
				//#pragma clang diagnostic push
				//#pragma clang diagnostic ignored "-Wformat-security"
				//// call fd printf with packed arguments
				//dprintf(_tty.get(), msg, xns::forward<A>(args)...);
				//#pragma clang diagnostic pop
			}


	};

}

#endif // XF_DEBUG_HPP
