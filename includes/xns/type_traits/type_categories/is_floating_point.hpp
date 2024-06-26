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

#ifndef XNS_IS_FLOATING_POINT_HEADER
#define XNS_IS_FLOATING_POINT_HEADER

#include "xns/type_traits/other/is_one_of.hpp"
#include "xns/type_traits/type_transformations/remove_cvref.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  F L O A T I N G  P O I N T -------------------------------------

	/* is floating point */
	template <typename ___type>
	concept is_floating_point = xns::is_one_of<xns::remove_cvref<___type>, float, double, long double>;

} // namespace xns

#endif // XNS_IS_FLOATING_POINT_HEADER
