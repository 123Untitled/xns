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

#ifndef XNS_IS_TRIVIALLY_MOVE_ASSIGNABLE_HEADER
#define XNS_IS_TRIVIALLY_MOVE_ASSIGNABLE_HEADER

#include "type_traits/supported_operations/is_trivially_assignable.hpp"
#include "type_traits/type_modifications/add_lvalue_reference.hpp"
#include "type_traits/type_modifications/add_rvalue_reference.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  T R I V I A L L Y  M O V E  A S S I G N A B L E ----------------

	/* is trivially move assignable */
	template <typename T>
	concept is_trivially_move_assignable
		= xns::is_trivially_assignable<xns::add_lvalue_reference<T>,
									   xns::add_rvalue_reference<T>>;

	/* are trivially move assignable */
	template <typename... T>
	concept are_trivially_move_assignable = (xns::is_trivially_move_assignable<T> && ...);

} // namespace xns

#endif // XNS_IS_TRIVIALLY_MOVE_ASSIGNABLE_HEADER
