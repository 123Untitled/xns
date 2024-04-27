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

#ifndef XNS_WMEMCHR_HEADER
#define XNS_WMEMCHR_HEADER

#include "xns/config/config.hpp"
#include "xns/type_traits/types.hpp"

#if !___xns_has_builtin(__builtin_wmemchr)
#	include <wchar.h>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- W M E M C H R ---------------------------------------------------------

	/* wmemchr */
	constexpr auto wmemchr(const wchar_t* ___s, const wchar_t ___wc, const xns::size_t ___sz) noexcept -> const wchar_t* {
		___xns_if_consteval {
			for (xns::size_t i = 0; i < ___sz; ++i) {
				if (___s[i] == ___wc)
					return &___s[i];
			} return nullptr;
		} else {
			#if ___xns_has_builtin(__builtin_wmemchr)
				return __builtin_wmemchr(___s, ___wc, ___sz);
			#else
				return ::wmemchr(___s, ___wc, ___sz);
			#endif
		}
	}

} // namespace xns

#endif // XNS_WMEMCHR_HEADER
