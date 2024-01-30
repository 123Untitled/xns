/*****************************************************************************/
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*****************************************************************************/

#pragma once

#ifndef XNS_IS_NOTHROW_MOVE_ASSIGNABLE_HPP
#define XNS_IS_NOTHROW_MOVE_ASSIGNABLE_HPP

#include "add_lvalue_reference.hpp"
#include "add_rvalue_reference.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  N O T H R O W  M O V E  A S S I G N A B L E --------------------

	/* is nothrow move assignable */
	template <typename T>
	concept is_nothrow_move_assignable
		= __is_nothrow_assignable(xns::add_lvalue_reference<T>,
								  xns::add_rvalue_reference<T>);

	/* are nothrow move assignable */
	template <typename... T>
	concept are_nothrow_move_assignable
		= (xns::is_nothrow_move_assignable<T> && ...);

} // namespace xns

#endif // XNS_IS_NOTHROW_MOVE_ASSIGNABLE_HPP
