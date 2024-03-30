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

#ifndef XNS_CLAMP_HEADER
#define XNS_CLAMP_HEADER

#include "xns/type_traits/relationships_and_property_queries/is_comparable.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- C L A M P -----------------------------------------------------------

	template <typename T>
	inline constexpr auto clamp(const T& value, const T& min, const T& max) -> T {
		// assert that T and U are comparable types
		static_assert(xns::is_comparable<T>, "): CLAMP: types must be comparable :(");
		// return clamped value
		return value < min ? min : value > max ? max : value;
	}

} // namespace xns

#endif // XNS_CLAMP_HEADER
