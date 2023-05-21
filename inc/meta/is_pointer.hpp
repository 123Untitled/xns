#ifndef IS_POINTER_HEADER
#define IS_POINTER_HEADER

#include "integral_constant.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  P O I N T E R --------------------------------------------------

	/* false type */
	template <class T>
	struct _is_pointer                    : xns::no  {};

	/* true type */
	template <class T>
	struct _is_pointer<T*>                : xns::yes {};

	/* true type */
	template <class T>
	struct _is_pointer<const T*>          : xns::yes {};

	/* true type */
	template <class T>
	struct _is_pointer<volatile T*>       : xns::yes {};

	/* true type */
	template <class T>
	struct _is_pointer<const volatile T*> : xns::yes {};


	/* is pointer concept */
	template <class T>
	concept is_pointer = _is_pointer<T>::value;

}

#endif
