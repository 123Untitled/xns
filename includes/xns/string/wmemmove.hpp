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

#ifndef XNS_WMEMMOVE_HEADER
#define XNS_WMEMMOVE_HEADER

#include "xns/config/config.hpp"
#include "xns/type_traits/types.hpp"

#if !___xns_has_builtin(__builtin_wmemmove)
#	include <wchar.h>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- W M E M M O V E -------------------------------------------------------

	/* wmemmove */
	constexpr auto wmemmove(wchar_t* ___dst, const wchar_t* ___src, const xns::size_t ___sz) noexcept -> wchar_t* {
		___xns_if_consteval {
			if (___dst < ___src) {
				for (xns::size_t i = 0; i < ___sz; ++i)
					___dst[i] = ___src[i];
			} else {
				for (xns::size_t i = ___sz; i > 0; --i)
					___dst[i - 1] = ___src[i - 1];
			} return ___dst;
		} else {
			#if ___xns_has_builtin(__builtin_wmemmove)
				return __builtin_wmemmove(___dst, ___src, ___sz);
			#else
				return ::wmemmove(___dst, ___src, ___sz);
			#endif
		}
	}

} // namespace xns

#endif // XNS_WMEMMOVE_HEADER
