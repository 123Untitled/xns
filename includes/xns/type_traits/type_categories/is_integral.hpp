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

#ifndef XNS_IS_INTEGRAL_HEADER
#define XNS_IS_INTEGRAL_HEADER

#include "xns/type_traits/other/is_one_of.hpp"
#include "xns/type_traits/type_modifications/remove_cv.hpp"

#include "xns/config/config.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  I N T E G R A L ------------------------------------------------

	/* is integral */
	template <typename __type>
	concept is_integral = xns::is_one_of<xns::remove_cv<__type>,

		bool, char, short, int, long, long long,
		char8_t, char32_t, char16_t, wchar_t,
		signed char, unsigned char, unsigned short,
		unsigned int, unsigned long, unsigned long long
			>;

} // namespace xns

#endif // XNS_IS_INTEGRAL_HEADER
