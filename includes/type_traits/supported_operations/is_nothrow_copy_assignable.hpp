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

#ifndef XNS_IS_NOTHROW_COPY_ASSIGNABLE_HPP
#define XNS_IS_NOTHROW_COPY_ASSIGNABLE_HPP

#include "add_const.hpp"
#include "add_lvalue_reference.hpp"
#include "config.hpp"

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

#if not XNS_HAS_BUILTIN(__is_nothrow_assignable)
#	error "compiler does not support __is_nothrow_assignable"
#endif

	// -- I S  N O T H R O W  C O P Y  A S S I G N A B L E --------------------

	/* is nothrow copy assignable */
	template <typename T>
	concept is_nothrow_copy_assignable
		= __is_nothrow_assignable(xns::add_lvalue_reference<T>,
								  xns::add_lvalue_reference<xns::add_const<T>>);

	/* are nothrow copy assignable */
	template <typename... T>
	concept are_nothrow_copy_assignable
		= (xns::is_nothrow_copy_assignable<T> && ...);

} // namespace xns

#endif // XNS_IS_NOTHROW_COPY_ASSIGNABLE_HPP



