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

#include "type_traits/other/is_one_of.hpp"
#include "type_traits/type_modifications/remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  F L O A T I N G  P O I N T -------------------------------------

	/* is floating point */
	template <typename __type>
	concept is_floating_point = xns::is_one_of<xns::remove_cv<__type>, float, double, long double>;

} // namespace xns

#endif // XNS_IS_FLOATING_POINT_HEADER
