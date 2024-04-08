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

#ifndef XNS_IS_NULL_POINTER_HEADER
#define XNS_IS_NULL_POINTER_HEADER

#include "xns/type_traits/relationships_and_property_queries/is_same.hpp"
#include "xns/type_traits/type_modifications/remove_cv.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  N U L L  P O I N T E R -----------------------------------------

	/* is null pointer */
	template <typename ___type>
	concept is_null_pointer = xns::is_same<xns::remove_cv<___type>, decltype(nullptr)>;

} // namespace xns

#endif // XNS_IS_NULL_POINTER_HEADER
