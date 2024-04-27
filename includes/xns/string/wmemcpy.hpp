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

#ifndef XNS_WMEMCPY_HEADER
#define XNS_WMEMCPY_HEADER

#include "xns/config/config.hpp"
#include "xns/type_traits/types.hpp"

#if !___xns_has_builtin(__builtin_wmemcpy)
#	include <wchar.h>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- W M E M C P Y ---------------------------------------------------------

	/* wmemcpy */
	constexpr auto wmemcpy(wchar_t* ___dst, const wchar_t* ___src, const xns::size_t ___sz) noexcept -> wchar_t* {
		___xns_if_consteval {
			for (xns::size_t i = 0; i < ___sz; ++i)
				___dst[i] = ___src[i];
			return ___dst;
		} else {
			#if ___xns_has_builtin(__builtin_wmemcpy)
				return __builtin_wmemcpy(___dst, ___src, ___sz);
			#else
				return ::wmemcpy(___dst, ___src, ___sz);
			#endif
		}
	}

} // namespace xns

#endif // XNS_WMEMCPY_HEADER
