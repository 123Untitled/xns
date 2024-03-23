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

#ifndef XNS_IS_MOVE_CONSTRUCTIBLE_HEADER
#define XNS_IS_MOVE_CONSTRUCTIBLE_HEADER

#include "xns/type_traits/supported_operations/is_constructible.hpp"
#include "xns/type_traits/type_modifications/add_rvalue_reference.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  M O V E  C O N S T R U C T I B L E -----------------------------

	/* is move constructible */
	template <typename T>
	concept is_move_constructible = xns::is_constructible<T, xns::add_rvalue_reference<T>>;

	/* are move constructible */
	template <typename... T>
	concept are_move_constructible = (xns::is_move_constructible<T> && ...);

} // namespace xns

#endif // XNS_IS_MOVE_CONSTRUCTIBLE_HEADER
