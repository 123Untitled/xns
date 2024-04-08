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

#ifndef XNS_IS_TRIVIAL_HEADER
#define XNS_IS_TRIVIAL_HEADER

#include "xns/config/config.hpp"

#if not XNS_HAS_BUILTIN(__is_trivial)
#	error "compiler does not support __is_trivial"
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  T R I V I A L --------------------------------------------------

	/* is trivial */
	template <typename ___type>
	concept is_trivial = __is_trivial(___type);

	/* are trivial */
	template <typename... ___types>
	concept are_trivial = (xns::is_trivial<___types> && ...);

} // namespace xns

#endif // XNS_IS_TRIVIAL_HEADER
