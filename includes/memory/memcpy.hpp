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

#ifndef XNS_MEMCPY_HEADER
#define XNS_MEMCPY_HEADER

// local headers
#include "config/os.hpp"
#include "type_traits/types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M E M C P Y ---------------------------------------------------------

	template <typename __dst, typename __src>
	inline auto memcpy(__dst* dst, const __src* src, const xns::size_t size) -> void {
		// check if types have the same size
		static_assert(sizeof(__dst) == sizeof(__src), "memcpy: types must have the same size");
		// call built-in memcpy
		__builtin_memcpy(dst, src, size);
	}

} // namespace xns

#endif // XNS_MEMCPY_HEADER











