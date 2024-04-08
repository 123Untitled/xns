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

#ifndef XNS_MOVE_HEADER
#define XNS_MOVE_HEADER

#include "xns/type_traits/other/to_reference.hpp"
#include "xns/type_traits/type_properties/is_const.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M O V E -------------------------------------------------------------

	/* move */
	template <typename ___type>
	constexpr auto move(___type&& obj) noexcept -> xns::to_rvalue<___type> {
		// remove reference from T and return as rvalue reference
		return static_cast<xns::to_rvalue<___type>>(obj);
	}

} // namespace xns

#endif // XNS_MOVE_HEADER
