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

#ifndef XNS_MEMSET_HEADER
#define XNS_MEMSET_HEADER

#include "xns/config/config.hpp"
#include "xns/type_traits/types.hpp"
#include "xns/memory/memcpy.hpp"
#include "xns/type_traits/language_support/is_constant_evaluated.hpp"

#if !___xns_has_builtin(__builtin_memset)
#	include <string.h>
#endif

#ifdef XNS_ARM
#	include <arm_neon.h>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M E M S E T ---------------------------------------------------------

	/* memset */
	template <typename ___type>
	constexpr auto memset(___type* ___dt, const ___type& ___vl, const xns::size_t ___sz) noexcept -> void {

		static_assert(xns::is_trivially_copyable<___type>,
				"memset: type must be trivially copyable");

		// consteval branch
		if constexpr (xns::is_constant_evaluated()) {
			for (___type* ___end = ___dt + ___sz; ___dt != ___end; ++___dt)
				*___dt = ___vl;
		}
		else if constexpr (sizeof(___type) == 1) {

			#if ___xns_has_builtin(__builtin_memset)
				__builtin_memset(___dt, ___vl, ___sz);
			#else
				::memset(___dt, ___vl, ___sz);
			#endif
		}
		else {

			for (xns::size_t i = 0; i < ___sz; ++i) {

				#if ___xns_has_builtin(__builtin_memcpy)
				__builtin_memcpy(___dt + i, &___vl, sizeof(___type));
				#else
				::memcpy(___dtc, &___vl, sizeof(___type));
				#endif
			}

		}

	
	}

} // namespace xns

#endif // XNS_MEMSET_HEADER
