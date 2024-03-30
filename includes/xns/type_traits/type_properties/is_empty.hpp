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

#include "xns/config/config.hpp"
#include "xns/type_traits/type_transformations/conditional.hpp"
#include "xns/type_traits/type_trait_constants/integral_constant.hpp"

#if not XNS_HAS_BUILTIN(__is_empty)
#	error "compiler does not support __is_empty"
#endif

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  E M P T Y ------------------------------------------------------

	/* is empty */
	template <typename ___type>
	concept is_empty = __is_empty(___type);

} // namespace xns

#endif // XNS_IS_EMPTY_HEADER
