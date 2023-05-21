#ifndef IS_VOID_HEADER
#define IS_VOID_HEADER

#include "integral_constant.hpp"

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  V O I D --------------------------------------------------------

	/* false type */
	template <class T>
	struct _is_void       : xns::no  {};

	/* true type */
	template <>
	struct _is_void<void> : xns::yes {};

	/* is void concept */
	template <class T>
	concept is_void = _is_void<T>::value;

	/* is not void concept */
	template <class T>
	concept is_not_void = !is_void<T>;


}


#endif
