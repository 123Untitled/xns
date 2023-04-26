#ifndef IS_POINTER_HEADER
#define IS_POINTER_HEADER

#include "integral_constant.hpp"

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- I S  P O I N T E R --------------------------------------------------

	/* is pointer false */
	template <class T>
	struct is_pointer                    : public false_t {};

	/* is pointer true */
	template <class T>
	struct is_pointer<T*>                : public true_t {};

	/* is const pointer true */
	template <class T>
	struct is_pointer<const T*>          : public true_t {};

	/* is volatile pointer true */
	template <class T>
	struct is_pointer<volatile T*>       : public true_t {};

	/* is const volatile pointer true */
	template <class T>
	struct is_pointer<const volatile T*> : public true_t {};

}

#endif
