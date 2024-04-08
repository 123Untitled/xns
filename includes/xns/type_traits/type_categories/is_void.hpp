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

#ifndef XNS_IS_VOID_HEADER
#define XNS_IS_VOID_HEADER

#include "xns/type_traits/relationships_and_property_queries/is_same.hpp"
#include "xns/type_traits/type_modifications/remove_cv.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  V O I D --------------------------------------------------------

	/* is void */
	template <typename ___type>
	concept is_void = xns::is_same<xns::remove_cv<___type>, void>;

} // namespace xns

#endif // XNS_IS_VOID_HEADER
