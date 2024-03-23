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

#ifndef XNS_IS_NOTHROW_COPY_ASSIGNABLE_HEADER
#define XNS_IS_NOTHROW_COPY_ASSIGNABLE_HEADER

#include "xns/type_traits/type_modifications/add_const.hpp"
#include "xns/type_traits/type_modifications/add_lvalue_reference.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_assignable.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  N O T H R O W  C O P Y  A S S I G N A B L E --------------------

	/* is nothrow copy assignable */
	template <typename T>
	concept is_nothrow_copy_assignable
		= xns::is_nothrow_assignable<xns::add_lvalue_reference<T>,
									 xns::add_lvalue_reference<xns::add_const<T>>>;

	/* are nothrow copy assignable */
	template <typename... T>
	concept are_nothrow_copy_assignable
		= (xns::is_nothrow_copy_assignable<T> && ...);

} // namespace xns

#endif // XNS_IS_NOTHROW_COPY_ASSIGNABLE_HEADER
