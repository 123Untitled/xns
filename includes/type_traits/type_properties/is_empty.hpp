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

#ifndef XNS_IS_EMPTY_HEADER
#define XNS_IS_EMPTY_HEADER

#include "config/config.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  E M P T Y ------------------------------------------------------

#if XNS_HAS_BUILTIN(__is_empty)

	/* is empty */
	template <typename T>
	concept is_empty = __is_empty(T);

#else
#	error "compiler does not support __is_empty"
#endif

} // namespace xns

#endif // XNS_IS_EMPTY_HEADER
