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

#ifndef XNS_IS_TRIVIALLY_ASSIGNABLE_HPP
#define XNS_IS_TRIVIALLY_ASSIGNABLE_HPP

#include "config.hpp"

#if not XNS_HAS_BUILTIN(__is_trivially_assignable)
#	include <type_traits>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


#if not XNS_HAS_BUILTIN(__is_trivially_assignable)

	/* is trivially assignable */
	template <typename T, typename A>
	concept is_trivially_assignable = std::is_trivially_assignable_v<T, A>;

#else

	// -- I S  T R I V I A L L Y  A S S I G N A B L E -------------------------

	/* is trivially assignable */
	template <typename T, typename A>
	concept is_trivially_assignable = __is_trivially_assignable(T, A);

#endif

} // namespace xns

#endif // XNS_IS_TRIVIALLY_ASSIGNABLE_HPP
