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

#ifndef XNS_IS_ASSIGNABLE_HPP
#define XNS_IS_ASSIGNABLE_HPP

#include "config.hpp"

#if not XNS_HAS_BUILTIN(__is_assignable)
#	include <type_traits>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


#if not XNS_HAS_BUILTIN(__is_assignable)

	/* is assignable */
	template <typename T, typename U>
	concept is_assignable = std::is_assignable_v<T, U>;

#else

	// -- I S  A S S I G N A B L E --------------------------------------------

	/* is assignable */
	template <typename T, typename U>
	concept is_assignable = __is_assignable(T, U);

#endif

} // namespace xns

#endif // XNS_IS_ASSIGNABLE_HPP
