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

#ifndef XNS_IS_BASE_OF_HEADER
#define XNS_IS_BASE_OF_HEADER

#include "type_traits/relationships_and_property_queries/is_derived_from.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  B A S E  O F ---------------------------------------------------

	/* is base of */
	template <typename __base, typename __derived>
	concept is_base_of = __impl::is_derived_from<__derived, __base>::value;

} // namespace xns

#endif // XNS_IS_DERIVED_FROM_HEADER

