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

#ifndef XNS_IS_COPY_ASSIGNABLE_HEADER
#define XNS_IS_COPY_ASSIGNABLE_HEADER

#include "xns/type_traits/supported_operations/is_assignable.hpp"
#include "xns/type_traits/type_modifications/add_lvalue_reference.hpp"
#include "xns/type_traits/type_modifications/add_const.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C O P Y  A S S I G N A B L E -----------------------------------

	/* is copy assignable */
	template <typename ___type>
	concept is_copy_assignable
		= xns::is_assignable<xns::add_lvalue_reference<___type>,
							 xns::add_lvalue_reference<xns::add_const<___type>>>;

	/* are copy assignable */
	template <typename... ___types>
	concept are_copy_assignable = (xns::is_copy_assignable<___types> && ...);

} // namespace xns

#endif // XNS_IS_COPY_ASSIGNABLE_HEADER
