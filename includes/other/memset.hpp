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

#ifndef XNS_MEMSET_HEADER
#define XNS_MEMSET_HEADER

// local headers
#include "type_traits/types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M E M S E T ---------------------------------------------------------

	/* memset */
	template <typename __type>
	inline auto memset(__type* dst, const __type& value, const xns::size_t size) -> void {
		// call builtin memset
		__builtin_memset(dst, value, size);
	}

} // namespace xns

#endif // XNS_MEMSET_HEADER
