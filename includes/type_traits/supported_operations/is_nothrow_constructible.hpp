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

#ifndef XNS_IS_NOTHROW_CONSTRUCTIBLE_HPP
#define XNS_IS_NOTHROW_CONSTRUCTIBLE_HPP

#include "config.hpp"

#if not XNS_HAS_BUILTIN(__is_nothrow_constructible)
#	include <type_traits>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


#if not XNS_HAS_BUILTIN(__is_nothrow_constructible)

	/* is nothrow constructible */
	template <typename T, typename... A>
	concept is_nothrow_constructible = std::is_nothrow_constructible_v<T, A...>;

#else

	// -- I S  N O T H R O W  C O N S T R U C T I B L E ------------------------

	/* is nothrow constructible */
	template <typename T, typename... A>
	concept is_nothrow_constructible = __is_nothrow_constructible(T, A...);

#endif

} // namespace xns

#endif // XNS_IS_NOTHROW_CONSTRUCTIBLE_HPP
