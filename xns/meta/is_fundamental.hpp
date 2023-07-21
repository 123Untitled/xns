#ifndef IS_FUNDAMENTAL_HEADER
#define IS_FUNDAMENTAL_HEADER

#include "is_arithmetic.hpp"
#include "is_void.hpp"
#include "is_null.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  F U N D A M E N T A L ------------------------------------------

	/* is fundamental concept */
	template <class T>
	concept is_fundamental = is_arithmetic<T> || is_void<T> || is_null<T>;


}


#endif
