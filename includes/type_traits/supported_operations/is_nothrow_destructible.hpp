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

#ifndef XNS_IS_NOTHROW_DESTRUCTIBLE_HEADER
#define XNS_IS_NOTHROW_DESTRUCTIBLE_HEADER

#include "other/config.hpp"

#if not XNS_HAS_BUILTIN(__is_nothrow_destructible)
#	error "compiler does not support __is_nothrow_destructible"
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  N O T H R O W  D E S T R U C T I B L E ----------------------------

	/* is nothrow destructible */
	template <typename T>
	concept is_nothrow_destructible = __is_nothrow_destructible(T);

	/* are nothrow destructible */
	template <typename... T>
	concept are_nothrow_destructible = (xns::is_nothrow_destructible<T> && ...);

} // namespace xns

#endif // XNS_IS_NOTHROW_DESTRUCTIBLE_HEADER
