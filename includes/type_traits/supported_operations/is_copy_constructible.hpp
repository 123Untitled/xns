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

#ifndef XNS_IS_COPY_CONSTRUCTIBLE_HPP
#define XNS_IS_COPY_CONSTRUCTIBLE_HPP

#include "config.hpp"
#include "add_lvalue_reference.hpp"
#include "add_const.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


#if not XNS_HAS_BUILTIN(__is_constructible)
#	error "compiler does not support __is_constructible"
#endif

	// -- I S  C O P Y  C O N S T R U C T I B L E -----------------------------

	/* is copy constructible */
	template <typename T>
	concept is_copy_constructible
		= __is_constructible(T, xns::add_lvalue_reference<xns::add_const<T>>);

	/* are copy constructible */
	template <typename... T>
	concept are_copy_constructible = (xns::is_copy_constructible<T> && ...);

} // namespace xns

#endif // XNS_IS_COPY_CONSTRUCTIBLE_HPP