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

#ifndef XNS_ADD_POINTER_HEADER
#define XNS_ADD_POINTER_HEADER

#include "xns/type_traits/type_categories/is_void.hpp"
#include "xns/type_traits/type_properties/is_referenceable.hpp"
#include "xns/type_traits/type_transformations/conditional.hpp"
#include "xns/type_traits/type_modifications/remove_reference.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A D D  P O I N T E R ------------------------------------------------

	/* add pointer */
	template <typename ___type>
	using add_pointer = xns::conditional<xns::is_void<___type> or xns::is_referenceable<___type>,
										 xns::remove_reference<___type>*,
										 ___type>;

} // namespace xns

#endif // XNS_ADD_POINTER_HEADER
