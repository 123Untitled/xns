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

#ifndef XNS_IS_SCALAR_HEADER
#define XNS_IS_SCALAR_HEADER

#include "xns/type_traits/type_categories/is_arithmetic.hpp"
#include "xns/type_traits/type_categories/is_member_pointer.hpp"
#include "xns/type_traits/type_categories/is_pointer.hpp"
#include "xns/type_traits/type_categories/is_null.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  S C A L A R ----------------------------------------------------

	/* is scalar */
	template <typename __type>
	concept is_scalar =    xns::is_arithmetic<__type>
						|| xns::is_member_pointer<__type>
						|| xns::is_pointer<__type>
						|| xns::is_null<__type>;

} // namespace xns

#endif // XNS_IS_SCALAR_HEADER
