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

#include "type_traits/type_modifications/remove.hpp"
#include "type_traits/type_categories/is_void.hpp"
#include "type_traits/type_properties/is_referenceable.hpp"
#include "type_traits/type_transformations/conditional.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A D D  P O I N T E R ------------------------------------------------

	/* add pointer */
	template <typename T>
	using add_pointer = xns::conditional<xns::is_void<T> or xns::is_referenceable<T>,
										 xns::remove_reference<T>*,
										 T>;

} // namespace xns

#endif // XNS_ADD_POINTER_HEADER
