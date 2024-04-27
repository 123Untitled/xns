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

#ifndef XNS_MEMCPY_HEADER
#define XNS_MEMCPY_HEADER

#include "xns/config/config.hpp"
#include "xns/type_traits/type_properties/is_trivially_copyable.hpp"

#if !___xns_has_builtin(__builtin_memcpy)
#	include <string.h>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M E M C P Y ---------------------------------------------------------

	/* memcpy */
	template <typename ___type>
	constexpr auto memcpy(___type* ___dst, const ___type* ___src, const decltype(sizeof(0)) ___sz) noexcept -> void {

		static_assert(xns::is_trivially_copyable<___type>,
			"memcpy requires trivially copyable type");

		if consteval {

			for (decltype(sizeof(0)) i = 0U; i < ___sz; ++i)
				___dst[i] = ___src[i];
		}
		else {
			#if ___xns_has_builtin(__builtin_memcpy)
				static_cast<void>(__builtin_memcpy(___dst, ___src, ___sz * sizeof(___type)));
			#else
				static_cast<void>(::memcpy(___dst, ___src, ___sz * sizeof(___type)));
			#endif
		}
	}

} // namespace xns

#endif // XNS_MEMCPY_HEADER
