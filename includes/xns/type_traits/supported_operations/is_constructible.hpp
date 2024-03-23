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

#ifndef XNS_IS_CONSTRUCTIBLE_HEADER
#define XNS_IS_CONSTRUCTIBLE_HEADER

#include "xns/config/config.hpp"

#if not XNS_HAS_BUILTIN(__is_constructible)
#	error "compiler does not support __is_constructible"
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C O N S T R U C T I B L E --------------------------------------

	/* is constructible */
	template <typename __type, typename... __params>
	concept is_constructible = __is_constructible(__type, __params...);

} // namespace xns

#endif // IS_CONSTRUCTIBLE_HEADER
