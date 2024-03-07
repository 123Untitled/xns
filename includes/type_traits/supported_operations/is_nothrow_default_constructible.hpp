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

#ifndef XNS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_HPP
#define XNS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_HPP

#include "config.hpp"

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

#if not XNS_HAS_BUILTIN(__is_nothrow_constructible)
#	error "compiler does not support __is_nothrow_constructible"
#endif


	// -- I S  N O T H R O W  D E F A U L T  C O N S T R U C T I B L E --------

	/* is nothrow default constructible */
	template <typename T>
	concept is_nothrow_default_constructible
		= __is_nothrow_constructible(T);

	/* are nothrow default constructible */
	template <typename... T>
	concept are_nothrow_default_constructible
		= (xns::is_nothrow_default_constructible<T> && ...);

} // namespace xns

#endif // XNS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_HPP
