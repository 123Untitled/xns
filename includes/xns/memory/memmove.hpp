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

#ifndef XNS_MEMMOVE_HEADER
#define XNS_MEMMOVE_HEADER

// local headers
#include "xns/type_traits/types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M E M M O V E -------------------------------------------------------

	/* memmove */
	template <typename __dst, typename __src>
	inline auto memmove(__dst* dst, const __src* src, const xns::size_t size) -> void {
		// check if types have the same size
		static_assert(sizeof(__dst) == sizeof(__src), "memmove: types must have the same size");
		// call built-in memmove
		__builtin_memmove(dst, src, size);
	}

} // namespace xns

#endif // XNS_MEMMOVE_HEADER
