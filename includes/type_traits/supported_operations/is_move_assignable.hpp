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

#ifndef XNS_IS_MOVE_ASSIGNABLE_HPP
#define XNS_IS_MOVE_ASSIGNABLE_HPP

#include "is_assignable.hpp"
#include "add_lvalue_reference.hpp"
#include "add_rvalue_reference.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  M O V E  A S S I G N A B L E -----------------------------------

	/* is move assignable */
	template <typename T>
	concept is_move_assignable = xns::is_assignable<xns::add_lvalue_reference<T>,
													xns::add_rvalue_reference<T>>;

	/* are move assignable */
	template <typename... T>
	concept are_move_assignable = (xns::is_move_assignable<T> && ...);

} // namespace xns

#endif // XNS_IS_MOVE_ASSIGNABLE_HPP
