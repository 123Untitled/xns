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

#ifndef XNS_SWAP_HEADER
#define XNS_SWAP_HEADER

// local headers
#include "type_traits/relationships_and_property_queries/is_convertible.hpp"
#include "type_traits/type_operations/move.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  S W A P P A B L E ----------------------------------------------

	template <typename T>
	concept is_swappable = requires(T a, T b) {
		{ a.swap(b) } -> xns::is_convertible<void>;
	};


	// -- S W A P  F U N C T I O N --------------------------------------------

	template <typename T>
	inline constexpr auto swap(T& a, T& b) -> void {
		// check if T is swappable
		if constexpr (xns::is_swappable<T>) {
			a.swap(b);
		}
		else {
			T tmp = xns::move(a);
				a = xns::move(b);
				b = xns::move(tmp);
		}
	}


}

#endif // SWAP_HEADER


