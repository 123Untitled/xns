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
	template <typename T>
	concept is_nothrow_move_constructible
		= xns::is_nothrow_constructible<T, xns::add_rvalue_reference<T>>;

	/* are nothrow move constructible */
	template <typename... T>
	concept are_nothrow_move_constructible
		= (xns::is_nothrow_move_constructible<T> && ...);

} // namespace xns

#endif // XNS_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HEADER
