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

#ifndef IS_NOTHROW_ASSIGNABLE_HEADER
#define IS_NOTHROW_ASSIGNABLE_HEADER

#include "xns/config/config.hpp"

#if not ___xns_has_builtin(__is_nothrow_assignable)
#	error "compiler does not support __is_nothrow_assignable"
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  N O T H R O W  A S S I G N A B L E -----------------------------

	/* is nothrow assignable */
	template <typename __type, typename __other>
	concept is_nothrow_assignable = __is_nothrow_assignable(__type, __other);

} // namespace xns

#endif // IS_NOTHROW_ASSIGNABLE_HEADER
