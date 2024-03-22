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

#ifndef XNS_SMALLER_TYPE_HEADER
#define XNS_SMALLER_TYPE_HEADER

// local headers
#include "type_traits/type_transformations/conditional.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S M A L L E R  T Y P E ----------------------------------------------

	/* smaller type */
	template <typename __first, typename __second>
	using smaller_type = xns::conditional<(sizeof(__first) < sizeof(__second)), __first, __second>;

} // namespace xns

#endif // XNS_SMALLER_TYPE_HEADER
