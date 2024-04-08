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

#ifndef XNS_IS_ENUM_HEADER
#define XNS_IS_ENUM_HEADER

#include "xns/config/config.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  E N U M --------------------------------------------------------

#if XNS_HAS_BUILTIN(__is_enum)

	/* is enum */
	template <typename ___type>
	concept is_enum = __is_enum(___type);

#else
#	error "Compiler does not support __is_enum."
#endif

} // namespace xns

#endif // XNS_IS_ENUM_HEADER
