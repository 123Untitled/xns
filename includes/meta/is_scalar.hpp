#ifndef XNS_IS_SCALAR_HEADER
#define XNS_IS_SCALAR_HEADER

#include "is_arithmetic.hpp"
#include "is_member_pointer.hpp"
#include "is_pointer.hpp"
#include "is_null.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  S C A L A R ----------------------------------------------------

	/* is scalar concept */
	template <class T>
	concept is_scalar =    is_arithmetic<T>
						|| is_member_pointer<T>
						|| is_pointer<T>
						|| is_null<T>;

}

#endif
