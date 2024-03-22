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

#ifndef XNS_IS_NOTHROW_CONSTRUCTIBLE_HEADER
#define XNS_IS_NOTHROW_CONSTRUCTIBLE_HEADER

#include "other/config.hpp"

#if not XNS_HAS_BUILTIN(__is_nothrow_constructible)
#	error "compiler does not support __is_nothrow_constructible"
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  N O T H R O W  C O N S T R U C T I B L E ------------------------

	/* is nothrow constructible */
	template <typename T, typename... A>
	concept is_nothrow_constructible = __is_nothrow_constructible(T, A...);

} // namespace xns

#endif // XNS_IS_NOTHROW_CONSTRUCTIBLE_HEADER
