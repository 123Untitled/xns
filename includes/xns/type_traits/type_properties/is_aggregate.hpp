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

#ifndef XNS_IS_AGGREGATE_HEADER
#define XNS_IS_AGGREGATE_HEADER

#include "xns/config/config.hpp"

#if not XNS_HAS_BUILTIN(__is_aggregate)
#	error "compiler does not support __is_aggregate"
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  A G G R E G A T E ------------------------------------------------

	/* is aggregate */
	template <typename ___type>
	concept is_aggregate = __is_aggregate(___type);

} // namespace xns

#endif // XNS_IS_AGGREGATE_HEADER
