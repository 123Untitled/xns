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

#ifndef XNS_MEMMOVE_HEADER
#define XNS_MEMMOVE_HEADER

#include "xns/config/config.hpp"
#include "xns/type_traits/types.hpp"

#if !___xns_has_builtin(__builtin_memmove)
#	include <string.h>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M E M M O V E -------------------------------------------------------

	/* memmove */
	constexpr auto memmove(void* ___dst, const void* ___src, const xns::size_t ___sz) noexcept -> void* {
		___xns_if_consteval {
			if (___dst < ___src) {
				for (xns::size_t i = 0; i < ___sz; ++i)
					static_cast<unsigned char*>(___dst)[i] = static_cast<const unsigned char*>(___src)[i];
			} else {
				for (xns::size_t i = ___sz; i > 0; --i)
					static_cast<unsigned char*>(___dst)[i - 1] = static_cast<const unsigned char*>(___src)[i - 1];
			} return ___dst;
		} else {
			#if ___xns_has_builtin(__builtin_memmove)
				return __builtin_memmove(___dst, ___src, ___sz);
			#else
				return ::memmove(___dst, ___src, ___sz);
			#endif
		}
	}

} // namespace xns

#endif // XNS_MEMMOVE_HEADER
