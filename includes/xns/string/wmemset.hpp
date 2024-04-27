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

#ifndef XNS_WMEMSET_HEADER
#define XNS_WMEMSET_HEADER

#include "xns/config/config.hpp"
#include "xns/type_traits/types.hpp"

#if !___xns_has_builtin(__builtin_wmemset)
#	include <wchar.h>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- W M E M S E T -------------------------------------------------------

	/* wmemset */
	constexpr auto wmemset(wchar_t* ___dst, const wchar_t ___wc, const xns::size_t ___sz) noexcept -> wchar_t* {
		___xns_if_consteval {
			for (xns::size_t i = 0; i < ___sz; ++i)
				___dst[i] = ___wc;
			return ___dst;
		} else {
			#if ___xns_has_builtin(__builtin_wmemset)
				return __builtin_wmemset(___dst, ___wc, ___sz); }
			#else
				return ::wmemset(___dst, ___wc, ___sz);
			#endif
		}
	}

} // namespace xns

#endif // XNS_WMEMSET_HEADER
