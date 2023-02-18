#ifndef XF_DEBUG_HPP
#define XF_DEBUG_HPP

#include <iostream>
#include <fcntl.h>
#include <types.hpp>
#include <unistd.h>
#include <type_traits.hpp>
#include <cstdio>

namespace Xf {

	// -- D E B U G  C L A S S ------------------------------------------------

	class Debug {

		public:
			static int _tty;

			static int initialize(const char* = nullptr);

			static void write(const void*, UInt64 = 0);

			template <typename... A>
			static void print(const char* msg, A&&... args) {
				// exit if no message or tty not open
				if (!msg)     { return; }
				if (_tty < 0) { return; }
				// avoid format-security warning
				#pragma clang diagnostic push
				#pragma clang diagnostic ignored "-Wformat-security"
				// call fd printf with packed arguments
				dprintf(_tty, msg, Xf::forward<A>(args)...);
				#pragma clang diagnostic pop
			}


	};

}

#endif // XF_DEBUG_HPP
