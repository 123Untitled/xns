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

#include "xns/type_traits/type_categories/is_char.hpp"
#include "xns/config/config.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- forward declarations ------------------------------------------------

	/* basic_string */
	template <typename>
	class basic_string;


	// -- S T R L E N ---------------------------------------------------------

	/* strlen */
	template <typename ___char>
	constexpr auto strlen(const ___char* ___str) noexcept -> typename basic_string<___char>::size_type {
		// check ___char is a character type
		static_assert(xns::is_char<___char>, "strlen: requires a character type");


#if XNS_CPP_VERSION > 20

		if consteval {
			// check if ___str is a null pointer
			if (___str == nullptr)
				return 0U;
			typename basic_string<___char>::size_type ___len = 0U;
			for (; ___str[___len] != 0; ++___len);
			return ___len;
			
		}
		else
#endif

		// return compiler builtin
		return __builtin_strlen(reinterpret_cast<const char*>(___str));
	}

} // namespace xns

#endif // XNS_STRLEN_HEADER
