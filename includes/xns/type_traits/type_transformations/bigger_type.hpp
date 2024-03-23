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

#ifndef XNS_BIGGER_TYPE_HEADER
#define XNS_BIGGER_TYPE_HEADER

// local headers
#include "xns/type_traits/type_transformations/conditional.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- B I G G E R  T Y P E ------------------------------------------------

	/* bigger type */
	template <typename __first, typename __second>
	using bigger_type = xns::conditional<(sizeof(__first) > sizeof(__second)), __first, __second>;

} // namespace xns

#endif // XNS_BIGGER_TYPE_HEADER

