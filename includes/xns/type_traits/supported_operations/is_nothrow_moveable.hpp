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

#ifndef XNS_IS_NOTHROW_MOVEABLE_HEADER
#define XNS_IS_NOTHROW_MOVEABLE_HEADER

#include "xns/type_traits/supported_operations/is_nothrow_move_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_assignable.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- N O T H R O W  M O V E A B L E ----------------------------------------

	/* nothrow moveable */
	template <typename ___type>
	concept is_nothrow_moveable = xns::is_nothrow_move_constructible<___type>
							&& xns::is_nothrow_move_assignable<___type>;

	/* are nothrow moveable */
	template <typename... ___type>
	concept are_nothrow_moveable = (xns::is_nothrow_moveable<___type> && ...);

} // namespace xns

#endif // XNS_IS_NOTHROW_MOVEABLE_HEADER
