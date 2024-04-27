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

#ifndef XNS_WMEMCMP_HEADER
#define XNS_WMEMCMP_HEADER

#include "xns/config/config.hpp"
#include "xns/type_traits/types.hpp"

#if !___xns_has_builtin(__builtin_wmemcmp)
#	include <wchar.h>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- W M E M C M P ---------------------------------------------------------

	/* wmemcmp */
	constexpr auto wmemcmp(const wchar_t* ___s1, const wchar_t* ___s2, const xns::size_t ___sz) noexcept -> int {
		___xns_if_consteval {
			for (xns::size_t i = 0; i < ___sz; ++i) {
				if (___s1[i] != ___s2[i])
					return ___s1[i] - ___s2[i];
			} return 0;
		} else {
			#if ___xns_has_builtin(__builtin_wmemcmp)
				return __builtin_wmemcmp(___s1, ___s2, ___sz);
			#else
				return ::wmemcmp(___s1, ___s2, ___sz);
			#endif
		}
	}

} // namespace xns

#endif // XNS_WMEMCMP_HEADER
