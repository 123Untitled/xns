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
#include "xns/type_traits/relationships_and_property_queries/is_convertible.hpp"
#include "xns/type_traits/type_operations/move.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_assignable.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  S W A P P A B L E ----------------------------------------------

	template <typename ___type>
	concept is_swappable = requires(___type ___a, ___type ___b) {
		{ ___a.swap(___b) } -> xns::is_convertible<void>;
	};


	// -- S W A P -------------------------------------------------------------

	template <typename ___type>
	constexpr auto swap(___type& ___a, ___type& ___b) noexcept -> void {
		// check if ___type is swappable
		if constexpr (xns::is_swappable<___type>) {
			___a.swap(___b);
			static_assert(noexcept(___a.swap(___b)),
					"swap is not noexcept");
		}
		else {
			___type ___tmp = xns::move(___a);
				___a = xns::move(___b);
				___b = xns::move(___tmp);
			static_assert(xns::is_nothrow_move_constructible<___type>
						&& xns::is_nothrow_move_assignable<___type>,
					"swap is not noexcept");
		}
	}

} // namespace xns

#endif // XNS_SWAP_HEADER
