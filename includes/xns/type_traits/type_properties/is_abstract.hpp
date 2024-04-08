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

#ifndef XNS_IS_ABSTRACT_HEADER
#define XNS_IS_ABSTRACT_HEADER

#include "xns/config/config.hpp"

#if not XNS_HAS_BUILTIN(__is_abstract)
#	error "compiler does not support __is_abstract"
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  A B S T R A C T ------------------------------------------------

	/* is abstract */
	template <typename ___type>
	concept is_abstract = __is_abstract(___type);

} // namespace xns

#endif // XNS_IS_ABSTRACT_HEADER
