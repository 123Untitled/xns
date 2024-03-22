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

#ifndef XNS_IS_COPY_CONSTRUCTIBLE_HEADER
#define XNS_IS_COPY_CONSTRUCTIBLE_HEADER

#include "type_traits/supported_operations/is_constructible.hpp"
#include "type_traits/type_modifications/add_lvalue_reference.hpp"
#include "type_traits/type_modifications/add_const.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C O P Y  C O N S T R U C T I B L E -----------------------------

	/* is copy constructible */
	template <typename __type>
	concept is_copy_constructible = xns::is_constructible<__type, xns::add_lvalue_reference<xns::add_const<__type>>>;

	/* are copy constructible */
	template <typename... __type>
	concept are_copy_constructible = (xns::is_copy_constructible<__type> && ...);

} // namespace xns

#endif // XNS_IS_COPY_CONSTRUCTIBLE_HEADER
