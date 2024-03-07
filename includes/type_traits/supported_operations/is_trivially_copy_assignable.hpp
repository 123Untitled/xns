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

#ifndef XNS_IS_TRIVIALLY_COPY_ASSIGNABLE_HPP
#define XNS_IS_TRIVIALLY_COPY_ASSIGNABLE_HPP

#include "is_trivially_assignable.hpp"
#include "add_lvalue_reference.hpp"
#include "add_const.hpp"
#include "config.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

#if not XNS_HAS_BUILTIN(__is_trivially_assignable)
#	error "compiler does not support __is_trivially_assignable"
#endif

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

#endif // XNS_IS_TRIVIALLY_COPY_ASSIGNABLE_HPP
