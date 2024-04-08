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

#ifndef XNS_REMOVE_CVREF_HEADER
#define XNS_REMOVE_CVREF_HEADER

#include "xns/type_traits/type_modifications/remove_cv.hpp"
#include "xns/type_traits/type_modifications/remove_reference.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E M O V E  C V R E F ----------------------------------------------

	/* remove cvref */
	template <typename ___type>
	using remove_cvref = xns::remove_cv<xns::remove_reference<___type>>;

} // namespace xns

#endif // XNS_REMOVE_CVREF_HEADER
