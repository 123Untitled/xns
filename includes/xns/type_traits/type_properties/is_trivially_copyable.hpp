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

#ifndef XNS_IS_TRIVIALLY_COPYABLE_HEADER
#define XNS_IS_TRIVIALLY_COPYABLE_HEADER

#include "xns/type_traits/types.hpp"
#include "xns/config/config.hpp"

#if not XNS_HAS_BUILTIN(__is_trivially_copyable)
#	error "compiler does not support __is_trivially_copyable"
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  T R I V I A L L Y  C O P Y A B L E -----------------------------

	/* is trivially copyable */
	template <typename ___type>
	concept is_trivially_copyable = __is_trivially_copyable(___type);

	/* are trivially copyable */
	template <typename... ___types>
	concept are_trivially_copyable = (xns::is_trivially_copyable<___types> && ...);

	/* is cheap to copy */
	template <typename ___type>
	concept is_cheap_to_copy = xns::is_trivially_copyable<___type>
							&& sizeof(___type) <= sizeof(xns::intmax_t);

	/* are cheap to copy */
	template <typename... ___types>
	concept are_cheap_to_copy = (xns::is_cheap_to_copy<___types> && ...);

} // namespace xns

#endif // XNS_IS_TRIVIALLY_COPYABLE_HPP
