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

#ifndef XNS_IS_CONSTRUCTIBLE_HPP
#define XNS_IS_CONSTRUCTIBLE_HPP

#include "config.hpp"

#if not XNS_HAS_BUILTIN(__is_constructible)
#	include <type_traits>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


#if not XNS_HAS_BUILTIN(__is_constructible)

	/* is constructible */
	template <typename T, typename... A>
	concept is_constructible = std::is_constructible_v<T, A...>;

#else

	// -- I S  C O N S T R U C T I B L E --------------------------------------

	/* is constructible */
	template <typename T, typename... A>
	concept is_constructible = __is_constructible(T, A...);

#endif

} // namespace xns

#endif // IS_CONSTRUCTIBLE_HPP
