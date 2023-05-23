#ifndef IS_NULL_HEADER
#define IS_NULL_HEADER

#include "is_same.hpp"
#include "types.hpp"
#include "remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  N U L L --------------------------------------------------------

	/* is null concept */
	template <class T>
	concept is_null = xns::is_same<xns::remove_cv<T>, xns::null>;


}


#endif
