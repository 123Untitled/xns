#ifndef XNS_COMPARE_HEADER
#define XNS_COMPARE_HEADER

#include "type_traits/type_transformations/conditional.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- L E S S  T Y P E ----------------------------------------------------

	/* less type */
	template <class T, class U>
	using less = xns::conditional<(sizeof(T) < sizeof(U)), T, U>;


	// -- G R E A T E R  T Y P E ----------------------------------------------

	/* greater type */
	template <class T, class U>
	using greater = xns::conditional<(sizeof(T) > sizeof(U)), T, U>;


}


#endif
