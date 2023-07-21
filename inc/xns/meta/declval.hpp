#ifndef DECLVAL_HEADER
#define DECLVAL_HEADER

#include <type_traits>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	template<typename T>
	constexpr bool always_false = false;

	// -- D E C L V A L ---------------------------------------------------------

	/* declval */
	template <class T>
	typename std::add_rvalue_reference<T>::type declval(void) noexcept {

		static_assert(always_false<T>, "DECLVAL NOT ALLOWED IN AN EVALUATED CONTEXT");
	}


}

#endif
