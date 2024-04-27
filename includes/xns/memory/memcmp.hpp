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

#ifndef XNS_MEMCMP_HEADER
#define XNS_MEMCMP_HEADER

#include "xns/config/config.hpp"
#include "xns/type_traits/types.hpp"

#if !___xns_has_builtin(__builtin_memcmp)
#	include <string.h>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M E M C M P -----------------------------------------------------------

	/* memcmp */
	constexpr auto memcmp(const void* ___s1, const void* ___s2, const xns::size_t ___sz) noexcept -> int {
		___xns_if_consteval {
			const unsigned char* ___p1 = static_cast<const unsigned char*>(___s1);
			const unsigned char* ___p2 = static_cast<const unsigned char*>(___s2);
			for (xns::size_t i = 0; i < ___sz; ++i) {
				if (___p1[i] != ___p2[i])
					return ___p1[i] - ___p2[i];
			} return 0;
		} else {
			#if ___xns_has_builtin(__builtin_memcmp)
				return __builtin_memcmp(___s1, ___s2, ___sz);
			#else
				return ::memcmp(___s1, ___s2, ___sz);
			#endif
		}
	}

} // namespace xns

#endif // XNS_MEMCMP_HEADER
