/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_SYSTEM_HEADER
#define XNS_SYSTEM_HEADER

// local headers
#include "type_traits/types.hpp"
#include "config/os.hpp"

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
				static const xns::size_t __line = []() -> xns::size_t {

					#if defined(XNS_APPLE)

					xns::size_t size = 0;
					xns::size_t _sizeof = sizeof(size);
					::sysctlbyname("hw.cachelinesize", &size, &_sizeof, nullptr, 0);
					std::cout << "cache line size: " << size << std::endl;
					return size;

					#else

					auto line = ::sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
					if (line == -1) {
						std::cerr << "sysconf(_SC_LEVEL1_DCACHE_LINESIZE) failed" << std::endl;
						return 0;
					}
					else return static_cast<xns::size_t>(line);

					#endif
				}();
				return __line;
			}



	};

}

#endif // SYSTEM_HEADER
