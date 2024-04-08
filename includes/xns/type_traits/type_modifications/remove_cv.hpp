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

#ifndef XNS_REMOVE_CV_HEADER
#define XNS_REMOVE_CV_HEADER

#include "xns/type_traits/type_modifications/remove_const.hpp"
#include "xns/type_traits/type_modifications/remove_volatile.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E M O V E  C V ----------------------------------------------------

	/* remove cv */
	template <typename ___type>
	using remove_cv = xns::remove_volatile<xns::remove_const<___type>>;

} // namespace xns

#endif // XNS_REMOVE_CV_HEADER
