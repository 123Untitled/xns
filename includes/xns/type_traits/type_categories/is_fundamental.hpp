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
#include "xns/type_traits/type_categories/is_null_pointer.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  F U N D A M E N T A L ------------------------------------------

	/* is fundamental */
	template <typename ___type>
	concept is_fundamental = xns::is_arithmetic<___type>
						  || xns::is_null_pointer<___type>
						  || xns::is_void<___type>;

} // namespace xns

#endif // XNS_IS_FUNDAMENTAL_HEADER
