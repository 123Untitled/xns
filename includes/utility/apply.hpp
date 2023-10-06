#ifndef XNS_APPLY_HEADER
#define XNS_APPLY_HEADER

// local headers
#include "is_function.hpp"
#include "tuple.hpp"
#include "integer_sequence.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A P P L Y -----------------------------------------------------------

	namespace impl {

		/* apply implementation */
		template <typename F, typename T, xns::size_t... I>
		constexpr auto apply(F&& function, T&& tuple, xns::index_seq<I...>) noexcept {
			return function(get<I>(xns::forward<T>(tuple))...);
		}

	}
	template <typename F, typename T>
	constexpr auto apply(F&& function, T&& tuple) noexcept -> auto {
		// check T is a tuple
		static_assert(xns::is_tuple<T>, "): APPLY: T IS NOT A TUPLE! :(");

		constexpr auto size = xns::tuple_size<T>;

		// check F is a function
		//static_assert(xns::is_function<F>, "): APPLY: F IS NOT A FUNCTION! :(");

		return impl::apply(xns::forward<F>(function),
						   xns::forward<T>(tuple),
						   xns::make_index_sequence<size>());
	}



}

#endif // APPLY_HEADER

