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

#ifndef XNS_IS_BOOL_HEADER
#define XNS_IS_BOOL_HEADER

#include "xns/type_traits/relationships_and_property_queries/is_same.hpp"
#include "xns/type_traits/type_modifications/remove_cv.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  B O O L ----------------------------------------------------------

	/* is bool */
	template <typename ___type>
	constexpr bool is_bool = xns::is_same<bool, xns::remove_cv<___type>>;

} // namespace xns

#endif // XNS_IS_BOOL_HEADER
