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

#include "xns/config/config.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  N O T H R O W  D E S T R U C T I B L E ----------------------------


#if XNS_HAS_BUILTIN(__is_nothrow_destructible)

	/* is nothrow destructible */
	template <typename ___type>
	concept is_nothrow_destructible = __is_nothrow_destructible(___type);

#else

	/* is nothrow destructible */
	template <typename ___type>
	concept is_nothrow_destructible = requires(___type ___obj) {
		{ ___obj.~___type() } noexcept;
	};

#endif

	/* are nothrow destructible */
	template <typename... T>
	concept are_nothrow_destructible = (xns::is_nothrow_destructible<T> && ...);

} // namespace xns

#endif // XNS_IS_NOTHROW_DESTRUCTIBLE_HEADER
