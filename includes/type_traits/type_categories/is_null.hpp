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

#ifndef XNS_IS_NULL_HEADER
#define XNS_IS_NULL_HEADER

#include "type_traits/relationships_and_property_queries/is_same.hpp"
#include "type_traits/type_modifications/remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  N U L L --------------------------------------------------------

	/* is null */
	template <typename __type>
	concept is_null = xns::is_same<xns::remove_cv<__type>, decltype(nullptr)>;

} // namespace xns

#endif // XNS_IS_NULL_HEADER
