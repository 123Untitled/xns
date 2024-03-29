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

#ifndef XNS_IS_COMPARABLE_HEADER
#define XNS_IS_COMPARABLE_HEADER

// local headers
#include "xns/type_traits/relationships_and_property_queries/is_convertible.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C O M P A R A B L E --------------------------------------------

	/* is comparable concept */
	template <typename A, typename B = A>
	concept is_comparable = requires (A a, B b) {
		{ a == b } -> xns::is_convertible<bool>;
		{ a != b } -> xns::is_convertible<bool>;
		{ a <  b } -> xns::is_convertible<bool>;
		{ a >  b } -> xns::is_convertible<bool>;
		{ a <= b } -> xns::is_convertible<bool>;
		{ a >= b } -> xns::is_convertible<bool>;
	};

} // namespace xns

#endif // IS_COMPARABLE_HEADER
