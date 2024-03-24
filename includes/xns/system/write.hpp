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

#ifndef XNS_WRITE_HEADER
#define XNS_WRITE_HEADER

#include "xns/type_traits/types.hpp"

#include <unistd.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- W R I T E -----------------------------------------------------------

	/* write */
	template <typename __type, xns::size_t __size>
	inline auto write(const int __fd, const __type (&__buffer)[__size]) noexcept -> auto {
		return ::write(__fd, __buffer, sizeof(__buffer));
	}

	/* write */
	template <typename __type>
	inline auto write(const int __fd, const __type& __buffer) noexcept -> auto {
		return ::write(__fd, &__buffer, sizeof(__buffer));
	}

	/* write */
	template <typename __type>
	inline auto write(const int __fd, const __type* __buffer __attribute__((nonnull)),
								  const xns::size_t __size) noexcept -> auto {
		return ::write(__fd, __buffer, __size);
	}

} // namespace xns

#endif // XNS_WRITE_HEADER
