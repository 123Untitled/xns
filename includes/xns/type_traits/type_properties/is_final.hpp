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

#ifndef XNS_IS_FINAL_HEADER
#define XNS_IS_FINAL_HEADER

#include "xns/config/config.hpp"

#if not XNS_HAS_BUILTIN(__is_final)
#	error "compiler does not support __is_final"
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  F I N A L ------------------------------------------------------

	/* is final */
	template <typename ___type>
	concept is_final = __is_final(___type);

} // namespace xns

#endif // XNS_IS_FINAL_HEADER
