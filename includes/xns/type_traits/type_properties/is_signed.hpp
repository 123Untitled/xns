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

#ifndef XNS_IS_SIGNED_HEADER
#define XNS_IS_SIGNED_HEADER

#include "xns/type_traits/type_categories/is_integral.hpp"
#include "xns/type_traits/type_categories/is_arithmetic.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  S I G N E D ----------------------------------------------------

	/* is signed */
	template <typename __type>
	concept is_signed = xns::is_arithmetic<__type> and (static_cast<__type>(-1) < static_cast<__type>(0));


	// -- I S  S I G N E D  I N T E G R A L -----------------------------------

	/* is signed integral */
	template <typename __type>
	concept is_signed_integral = xns::is_integral<__type> and xns::is_signed<__type>;

} // namespace xns

#endif // XNS_IS_SIGNED_HEADER
