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

#ifndef XNS_IS_DESTRUCTIBLE_HEADER
#define XNS_IS_DESTRUCTIBLE_HEADER

#include "config/config.hpp"

#if not XNS_HAS_BUILTIN(__is_destructible)
#	error "compiler does not support __is_destructible"
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  D E S T R U C T I B L E ----------------------------------------

	/* is destructible */
	template <typename T>
	concept is_destructible = __is_destructible(T);

	/* are destructible */
	template <typename... T>
	concept are_destructible = (xns::is_destructible<T> && ...);

} // namespace xns

#endif // XNS_IS_DESTRUCTIBLE_HEADER
