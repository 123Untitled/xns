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

#ifndef XNS_IS_ARITHMETIC_HEADER
#define XNS_IS_ARITHMETIC_HEADER

#include "xns/type_traits/type_categories/is_integral.hpp"
#include "xns/type_traits/type_categories/is_floating_point.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  A R I T H M E T I C --------------------------------------------

	/* is arithmetic concept */
	template <class T>
	concept is_arithmetic = xns::is_integral<T> || xns::is_floating_point<T>;

} // namespace xns

#endif // XNS_IS_ARITHMETIC_HEADER
