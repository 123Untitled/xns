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

#ifndef XNS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_HEADER
#define XNS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_HEADER

#include "xns/type_traits/supported_operations/is_trivially_constructible.hpp"
#include "xns/type_traits/type_modifications/add_rvalue_reference.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  T R I V I A L L Y  M O V E  C O N S T R U C T I B L E ----------

	/* is trivially move constructible */
	template <typename ___type>
	concept is_trivially_move_constructible =
		xns::is_trivially_constructible<___type, xns::add_rvalue_reference<___type>>;

	/* are trivially move constructible */
	template <typename... ___type>
	concept are_trivially_move_constructible = (xns::is_trivially_move_constructible<___type> && ...);

} // namespace xns

#endif // XNS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_HEADER
