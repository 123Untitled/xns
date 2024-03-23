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

#ifndef XNS_IS_TRIVIALLY_DESTRUCTIBLE_HEADER
#define XNS_IS_TRIVIALLY_DESTRUCTIBLE_HEADER

// local headers
#include "xns/config/config.hpp"
#include "xns/type_traits/supported_operations/is_destructible.hpp"

#if not XNS_HAS_BUILTIN(__is_trivially_destructible) and not XNS_HAS_BUILTIN(__has_trivial_destructor)
#	error "compiler does not support __is_trivially_destructible and __has_trivial_destructor"
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  T R I V I A L L Y  D E S T R U C T I B L E ----------------------

#if XNS_HAS_BUILTIN(__is_trivially_destructible)

	/* is trivially destructible concept */
	template <class T>
	concept is_trivially_destructible = __is_trivially_destructible(T);

#elif XNS_HAS_BUILTIN(__has_trivial_destructor)

	/* is trivially destructible concept */
	template <class T>
	concept is_trivially_destructible = xns::is_destructible<T> && __has_trivial_destructor(T);

#endif

} // namespace xns

#endif // IS_TRIVIALLY_DESTRUCTIBLE_HEADER
