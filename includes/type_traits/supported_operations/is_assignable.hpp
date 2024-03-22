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

#ifndef XNS_IS_ASSIGNABLE_HEADER
#define XNS_IS_ASSIGNABLE_HEADER

#include "config/config.hpp"

#if not XNS_HAS_BUILTIN(__is_assignable)
#	error "compiler does not support __is_assignable"
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  A S S I G N A B L E --------------------------------------------

	/* is assignable */
	template <typename __type, typename __other>
	concept is_assignable = __is_assignable(__type, __other);

} // namespace xns

#endif // XNS_IS_ASSIGNABLE_HEADER
