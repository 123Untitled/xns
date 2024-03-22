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

#include "type_traits/relationships_and_property_queries/is_same.hpp"
#include "type_traits/type_modifications/remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  B O O L ----------------------------------------------------------

	/* is bool */
	template <typename __type>
	constexpr bool is_bool = xns::is_same<bool, xns::remove_cv<__type>>;

} // namespace xns

#endif // XNS_IS_BOOL_HEADER
