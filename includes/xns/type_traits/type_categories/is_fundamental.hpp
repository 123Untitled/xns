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

#ifndef XNS_IS_FUNDAMENTAL_HEADER
#define XNS_IS_FUNDAMENTAL_HEADER

#include "xns/type_traits/type_categories/is_arithmetic.hpp"
#include "xns/type_traits/type_categories/is_void.hpp"
#include "xns/type_traits/type_categories/is_null.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  F U N D A M E N T A L ------------------------------------------

	/* is fundamental */
	template <class T>
	concept is_fundamental = xns::is_arithmetic<T> || xns::is_void<T> || xns::is_null<T>;

} // namespace xns

#endif // XNS_IS_FUNDAMENTAL_HEADER
