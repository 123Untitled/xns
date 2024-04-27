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

#ifndef XNS_WCSLEN_HEADER
#define XNS_WCSLEN_HEADER

#include "xns/config/config.hpp"
#include "xns/type_traits/types.hpp"

#if !___xns_has_builtin(__builtin_wcslen)
#	include <wchar.h>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- W C S L E N -----------------------------------------------------------

	/* wcslen */
	constexpr auto wcslen(const wchar_t* ___s) noexcept -> xns::size_t {
		___xns_if_consteval {
			xns::size_t ___sz = 0;
			while (___s[___sz] != L'\0') ++___sz;
			return ___sz;
		} else {
			#if ___xns_has_builtin(__builtin_wcslen)
				return __builtin_wcslen(___s);
			#else
				return ::wcslen(___s);
			#endif
		}
	}

} // namespace xns

#endif // XNS_WCSLEN_HEADER
