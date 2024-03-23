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

#ifndef XNS_APPLY_HEADER
#define XNS_APPLY_HEADER

// local headers
#include "xns/type_traits/type_categories/is_function.hpp"
#include "xns/type_traits/type_categories/is_member_pointer.hpp"
#include "xns/containers/tuple.hpp"
#include "xns/type_traits/sequences/integer_sequence.hpp"
#include "xns/invoke/invoke.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A P P L Y -----------------------------------------------------------


	// -- detail --------------------------------------------------------------

	namespace impl {

		/* apply implementation */
		template <typename F, typename T, xns::size_t... I>
		inline constexpr auto apply(F&& func, T&& tuple, xns::index_sequence<I...>) noexcept {
			return xns::invoke(xns::forward<F>(func),
							   xns::get<I>(xns::forward<T>(tuple))...);
		}

	}

	/* apply */
	template <typename F, typename T>
	inline constexpr auto apply(F&& function, T&& tuple) noexcept -> auto {
		// return implementation
		return impl::apply(xns::forward<F>(function),
						   xns::forward<T>(tuple),
						   xns::make_index_sequence<xns::tuple_size<T>>());
	}

} // namespace xns

#endif // XNS_APPLY_HPP

