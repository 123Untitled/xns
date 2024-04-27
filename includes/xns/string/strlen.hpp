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

#ifndef XNS_STRLEN_HEADER
#define XNS_STRLEN_HEADER

#include "xns/config/config.hpp"
#include "xns/type_traits/types.hpp"

#if !___xns_has_builtin(__builtin_strlen)
#	include <string.h>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S T R L E N ---------------------------------------------------------

	constexpr auto strlen(const char* str) noexcept -> xns::size_t {
		___xns_if_consteval {
			xns::size_t sz = 0;
			while (str[sz] != '\0') ++sz;
			return sz;
		} else {
			#if ___xns_has_builtin(__builtin_strlen)
				return __builtin_strlen(str);
			#else
				return ::strlen(str);
			#endif
		}
	}

} // namespace xns

#endif // XNS_STRLEN_HEADER
