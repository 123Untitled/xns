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

#ifndef IS_NOTHROW_ASSIGNABLE_HPP
#define IS_NOTHROW_ASSIGNABLE_HPP

#include "config.hpp"

#if not XNS_HAS_BUILTIN(__is_nothrow_assignable)
#	include <type_traits>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


#if not XNS_HAS_BUILTIN(__is_nothrow_assignable)

	/* is nothrow assignable */
	template <typename T, typename A>
	concept is_nothrow_assignable = std::is_nothrow_assignable_v<T, A>;

#else

	// -- I S  N O T H R O W  A S S I G N A B L E -----------------------------

	/* is nothrow assignable */
	template <typename T, typename A>
	concept is_nothrow_assignable = __is_nothrow_assignable(T, A);

#endif

} // namespace xns

#endif // IS_NOTHROW_ASSIGNABLE_HPP
