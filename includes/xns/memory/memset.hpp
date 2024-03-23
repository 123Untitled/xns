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
#include "xns/type_traits/types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M E M S E T ---------------------------------------------------------

	/* memset */
	template <typename __type>
	inline auto memset(__type* dst, const __type& value, const xns::size_t size) -> void {

		static_assert(sizeof(__type) <= sizeof(int), "memset: invalid type size");
		// call builtin memset
		__builtin_memset(dst, *reinterpret_cast<const int*>(&value), size);
	}

} // namespace xns

#endif // XNS_MEMSET_HEADER
