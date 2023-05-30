#ifndef IS_FLOATING_HEADER
#define IS_FLOATING_HEADER

#include "is_one_of.hpp"
#include "remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  F L O A T I N G  P O I N T -------------------------------------

	/* is floating concept */
	template <class T>
	concept is_floating = xns::is_one_of<xns::remove_cv<T>, float, double, long double>;


}


#endif

