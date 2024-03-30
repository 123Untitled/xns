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

#ifndef XNS_FLOOR_HEADER
#define XNS_FLOOR_HEADER

#include "xns/type_traits/type_categories/is_floating_point.hpp"
#include "xns/type_traits/types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- F L O O R -----------------------------------------------------------

	template <typename ___type>
	constexpr auto floor(const ___type& value) noexcept -> ___type {
		// assert that T is an floating point type
		static_assert(xns::is_floating_point<___type>, "floor: ___type must be a floating point type");
		// check sign
		return value > 0 ? static_cast<___type>(static_cast<xns::uintmax_t>(value))
						 : static_cast<___type>(static_cast<xns::intmax_t>(value)) - 1;
	}

} // namespace xns

#endif // XNS_FLOOR_HEADER
