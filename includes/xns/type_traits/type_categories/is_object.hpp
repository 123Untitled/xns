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

#ifndef XNS_IS_OBJECT_HEADER
#define XNS_IS_OBJECT_HEADER

#include "xns/type_traits/type_categories/is_scalar.hpp"
#include "xns/type_traits/type_categories/is_array.hpp"
#include "xns/type_traits/type_categories/is_union.hpp"
#include "xns/type_traits/type_categories/is_class.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  O B J E C T ----------------------------------------------------

	/* is object */
	template <typename ___type>
	concept is_object = (xns::is_scalar<___type> || xns::is_array<___type>
					  || xns::is_union<___type>  || xns::is_class<___type>);

	/* are object */
	template <typename... ___type>
	concept are_object = (xns::is_object<___type> && ...);

} // namespace xns

#endif // XNS_IS_OBJECT_HEADER
