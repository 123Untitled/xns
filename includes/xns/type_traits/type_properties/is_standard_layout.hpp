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

#ifndef XNS_IS_STANDARD_LAYOUT_HEADER
#define XNS_IS_STANDARD_LAYOUT_HEADER

#include "xns/config/config.hpp"

#if not XNS_HAS_BUILTIN(__is_standard_layout)
#	error "compiler does not support __is_standard_layout"
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  S T A N D A R D  L A Y O U T -----------------------------------

	/* is standard layout */
	template <typename ___type>
	concept is_standard_layout = __is_standard_layout(___type);

} // namespace xns

#endif // XNS_IS_STANDARD_LAYOUT_HEADER
