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

#ifndef XNS_CEIL_HEADER
#define XNS_CEIL_HEADER

#include "xns/type_traits/type_categories/is_floating_point.hpp"
#include "xns/type_traits/types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- C E I L -------------------------------------------------------------

	template <typename ___type>
	constexpr auto ceil(const ___type& value) noexcept -> ___type {
		// assert that type is an floating point type
		static_assert(xns::is_floating_point<___type>, "ceil: ___type must be a floating point type");
		// check sign
		return value > 0 ? static_cast<___type>(static_cast<xns::uintmax_t>(value)) + 1
						 : static_cast<___type>(static_cast<xns::intmax_t>(value));
	}

} // namespace xns

#endif // XNS_CEIL_HEADER
