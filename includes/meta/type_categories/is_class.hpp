#ifndef XNS_IS_CLASS_HEADER
#define XNS_IS_CLASS_HEADER

#include "is_union.hpp"
#include "integral_constant.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C L A S S ------------------------------------------------------

	// -- detail --------------------------------------------------------------

	namespace impl {

		/* test for class */
		template <typename T>
		constexpr auto test(int T::*) -> xns::bool_constant<xns::is_union<T> == false>;

		/* test for non-class */
		template <typename T>
		constexpr auto test(...) -> xns::no;

	}

	/* is_class */
	template <typename T>
	concept is_class = decltype(impl::test<T>(nullptr))::value;

}

#endif
