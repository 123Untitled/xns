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

#ifndef XNS_READ_HEADER
#define XNS_READ_HEADER

#include "xns/type_traits/type_properties/is_trivially_copyable.hpp"
#include "xns/type_traits/types.hpp"

#include <unistd.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E A D -------------------------------------------------------------

	/* read */
	template <typename __type, xns::size_t __size>
	inline auto read(const int __fd, __type (&__buffer)[__size]) noexcept -> auto {
		static_assert(xns::is_trivially_copyable<__type>, "type must be trivially copyable");
		return ::read(__fd, __buffer, sizeof(__buffer));
	}

	/* read */
	template <typename __type>
	inline auto read(const int __fd, __type& __buffer) noexcept -> auto {
		static_assert(xns::is_trivially_copyable<__type>, "type must be trivially copyable");
		return ::read(__fd, &__buffer, sizeof(__buffer));
	}

	/* read */
	template <typename __type>
	inline auto read(const int __fd, __type* __buffer __attribute__((nonnull)),
						   const xns::size_t __size) noexcept -> auto {
		static_assert(xns::is_trivially_copyable<__type>, "type must be trivially copyable");
		return ::read(__fd, __buffer, __size);
	}

} // namespace xns

#endif // XNS_READ_HEADER
