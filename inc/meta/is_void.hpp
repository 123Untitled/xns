#ifndef IS_VOID_HEADER
#define IS_VOID_HEADER

#include "is_same.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  V O I D --------------------------------------------------------

	/* is void concept */
	template <class T>
	concept is_void = xns::is_same<xns::remove_cv<T>, void>;


}


#endif
