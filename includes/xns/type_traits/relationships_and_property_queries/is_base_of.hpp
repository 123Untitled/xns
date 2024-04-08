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

#ifndef XNS_IS_BASE_OF_HEADER
#define XNS_IS_BASE_OF_HEADER

#include "xns/type_traits/relationships_and_property_queries/is_derived_from.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  B A S E  O F ---------------------------------------------------

	/* is base of */
	template <typename ___base, typename ___derived>
	concept is_base_of = xns::___impl::___is_derived_from<___derived, ___base>::value;

} // namespace xns

#endif // XNS_IS_DERIVED_FROM_HEADER

