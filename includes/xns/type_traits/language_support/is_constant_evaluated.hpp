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

#ifndef XNS_IS_CONSTANT_EVALUATED_HEADER
#define XNS_IS_CONSTANT_EVALUATED_HEADER

#include "xns/config/config.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C O N S T A N T  E V A L U A T E D -----------------------------

#if ___xns_has_builtin(__builtin_is_constant_evaluated)

	/* is constant evaluated */
	constexpr auto is_constant_evaluated(void) noexcept -> bool {
		return __builtin_is_constant_evaluated();
	}

#else
#	error "compiler does not support __builtin_is_constant_evaluated"
#endif

} // namespace xns

#endif // XNS_IS_CONSTANT_EVALUATED_HEADER
