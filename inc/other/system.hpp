#ifndef SYSTEM_HEADER
#define SYSTEM_HEADER

// local headers
#include "types.hpp"
#include "os.hpp"

#if defined(XNS_APPLE) || defined(XNS_BSD)
# include <sys/sysctl.h>
#else
# include <unistd.h>
#endif

// c++ standard library headers
#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S Y S T E M  C L A S S ----------------------------------------------

	class system final {


		public:


			/* get cache line size */
			inline static auto cache_line(void) -> xns::size_t {
				static const xns::size_t line = []() -> xns::size_t {
					#if defined(XNS_APPLE)
					xns::size_t size = 0;
					xns::size_t _sizeof = sizeof(size);
					::sysctlbyname("hw.cachelinesize", &size, &_sizeof, nullptr, 0);
					std::cout << "cache line size: " << size << std::endl;
					return size;
					#else
					return ::sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
					#endif
				}();
				return line;
			}



	};

}

#endif // SYSTEM_HEADER
