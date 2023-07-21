#ifndef IS_ARITHMETIC_HEADER
#define IS_ARITHMETIC_HEADER

#include "is_integral.hpp"
#include "is_floating.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  A R I T H M E T I C --------------------------------------------

	/* is arithmetic concept */
	template <class T>
	concept is_arithmetic = is_integral<T> || is_floating<T>;


}


#endif
