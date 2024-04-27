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

#ifndef XNS_MEMCHR_HEADER
#define XNS_MEMCHR_HEADER

#include "xns/config/config.hpp"
#include "xns/type_traits/types.hpp"

#if !___xns_has_builtin(__builtin_memchr)
#	include <string.h>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M E M C H R -----------------------------------------------------------

	/* memchr */
	template <typename ___type>
	constexpr auto memchr(const ___type* ___pt, const ___type& ___vl, const xns::size_t ___sz) noexcept -> const ___type* {
		for (xns::size_t i = 0; i < ___sz; ++i)
			if (___pt[i] == ___vl)
				return ___pt + i;
		return nullptr;
	}

} // namespace xns

#endif // XNS_MEMCHR_HEADER
