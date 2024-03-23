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

#ifndef XNS_IS_TRIVIALLY_COPY_ASSIGNABLE_HEADER
#define XNS_IS_TRIVIALLY_COPY_ASSIGNABLE_HEADER

#include "xns/type_traits/supported_operations/is_trivially_assignable.hpp"
#include "xns/type_traits/type_modifications/add_lvalue_reference.hpp"
#include "xns/type_traits/type_modifications/add_const.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  T R I V I A L L Y  C O P Y  A S S I G N A B L E ----------------

	/* is trivially copy assignable */
	template <typename T>
	concept is_trivially_copy_assignable
		= xns::is_trivially_assignable<xns::add_lvalue_reference<T>,
									   xns::add_lvalue_reference<xns::add_const<T>>>;

	/* are trivially copy assignable */
	template <typename... T>
	concept are_trivially_copy_assignable = (xns::is_trivially_copy_assignable<T> && ...);

} // namespace xns

#endif // XNS_IS_TRIVIALLY_COPY_ASSIGNABLE_HEADER
