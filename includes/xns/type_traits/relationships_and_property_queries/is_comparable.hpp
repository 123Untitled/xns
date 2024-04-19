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
	template <typename ___lhs, typename ___rhs = ___lhs>
	concept is_comparable = requires (___lhs ___l, ___rhs ___r) {
		{ ___l == ___r } -> xns::is_convertible<bool>;
		{ ___l != ___r } -> xns::is_convertible<bool>;
		{ ___l <  ___r } -> xns::is_convertible<bool>;
		{ ___l >  ___r } -> xns::is_convertible<bool>;
		{ ___l <= ___r } -> xns::is_convertible<bool>;
		{ ___l >= ___r } -> xns::is_convertible<bool>;
	};

	/* are comparable */
	template <typename ___type, typename... ___types>
	concept are_comparable = (xns::is_comparable<___type, ___types> && ...);

} // namespace xns

#endif // IS_COMPARABLE_HEADER
