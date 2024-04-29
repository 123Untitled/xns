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

#ifndef XNS_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HEADER
#define XNS_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HEADER

#include "xns/type_traits/type_modifications/add_rvalue_reference.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_constructible.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  N O T H R O W  M O V E  C O N S T R U C T I B L E ----------------

	/* is nothrow move constructible */
	template <typename ___type>
	concept is_nothrow_move_constructible
		= xns::is_nothrow_constructible<___type, xns::add_rvalue_reference<___type>>;

	/* are nothrow move constructible */
	template <typename... ___types>
	concept are_nothrow_move_constructible
		= (xns::is_nothrow_move_constructible<___types> && ...);

} // namespace xns

#endif // XNS_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HEADER
