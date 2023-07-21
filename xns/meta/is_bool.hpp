#ifndef IS_BOOL_HEADER
#define IS_BOOL_HEADER

#include "is_same.hpp"
#include "remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  B O O L ----------------------------------------------------------

	/* is bool */
	template <typename T>
	constexpr bool is_bool = xns::is_same<bool, xns::remove_cv<T>>;

}

#endif
