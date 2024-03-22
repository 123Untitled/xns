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

#ifndef XNS_IS_ONE_OF_HEADER
#define XNS_IS_ONE_OF_HEADER

#include "type_traits/relationships_and_property_queries/is_same.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  O N E  O F -----------------------------------------------------

	/* is one of */
	template <typename __type, typename... __types>
	concept is_one_of = (xns::is_same<__type, __types> || ...);

} // namespace xns

#endif // XNS_IS_ONE_OF_HEADER
