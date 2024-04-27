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

#ifndef XNS_MALLOC_HEADER
#define XNS_MALLOC_HEADER

#include "xns/config/config.hpp"
#include "xns/type_traits/types.hpp"
#include "xns/type_traits/type_properties/is_trivially_copyable.hpp"

#if    !___xns_has_builtin(__builtin_malloc)  \
	|| !___xns_has_builtin(__builtin_calloc)  \
	|| !___xns_has_builtin(__builtin_realloc) \
	|| !___xns_has_builtin(__builtin_free)
#	include <cstdlib>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M A L L O C -----------------------------------------------------------

	/* malloc */
	template <typename ___type>
	inline auto malloc(const xns::size_t ___sz) noexcept -> ___type* {

		#if ___xns_has_builtin(__builtin_malloc)
			return static_cast<___type*>(__builtin_malloc(___sz * sizeof(___type)));
		#else
			return static_cast<___type*>(::malloc(___sz * sizeof(___type)));
		#endif
	}

	/* calloc */
	template <typename ___type>
	inline auto calloc(const xns::size_t ___sz) noexcept -> ___type* {

		#if ___xns_has_builtin(__builtin_calloc)
			return static_cast<___type*>(__builtin_calloc(___sz, sizeof(___type)));
		#else
			return static_cast<___type*>(::calloc(___sz, sizeof(___type)));
		#endif
	}

	/* realloc */
	template <typename ___type>
	inline auto realloc(___type* ___ptr, const xns::size_t ___sz) noexcept -> ___type* {

		static_assert(xns::is_trivially_copyable<___type>,
				"realloc requires trivially copyable type");

		#if ___xns_has_builtin(__builtin_realloc)
			return static_cast<___type*>(__builtin_realloc(___ptr, ___sz * sizeof(___type)));
		#else
			return static_cast<___type*>(::realloc(___ptr, ___sz * sizeof(___type)));
		#endif
	}

	/* free */
	template <typename ___type>
	inline auto free(___type* ___ptr) noexcept -> void {

		#if ___xns_has_builtin(__builtin_free)
			__builtin_free(___ptr);
		#else
			::free(___ptr);
		#endif
	}

} // namespace xns

#endif // XNS_MALLOC_HEADER
