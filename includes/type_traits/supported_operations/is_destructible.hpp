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

#ifndef XNS_IS_DESTRUCTIBLE_HPP
#define XNS_IS_DESTRUCTIBLE_HPP

#include "config.hpp"

#if not XNS_HAS_BUILTIN(__is_destructible)
#	include <type_traits>
#endif

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


#if not XNS_HAS_BUILTIN(__is_destructible)

	/* is destructible */
	template <typename T>
	concept is_destructible = std::is_destructible_v<T>;

#else

	// -- I S  D E S T R U C T I B L E ----------------------------------------

	/* is destructible */
	template <typename T>
	concept is_destructible = __is_destructible(T);

#endif

	/* are destructible */
	template <typename... T>
	concept are_destructible = (xns::is_destructible<T> && ...);

} // namespace xns

#endif // XNS_IS_DESTRUCTIBLE_HPP
