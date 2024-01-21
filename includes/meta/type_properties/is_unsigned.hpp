#ifndef XNS_IS_UNSIGNED_HEADER
#define XNS_IS_UNSIGNED_HEADER

#include "is_integral.hpp"
#include "is_arithmetic.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace xns {


	// -- I S  U N S I G N E D ------------------------------------------------

	/* is unsigned */
	template <class T>
	concept is_unsigned = requires {
		// check if T is arithmetic
		requires xns::is_arithmetic<T>;
		// check if T is unsigned
		requires T(-1) > T(0);
	};


	// -- I S  U N S I G N E D  I N T E G R A L -------------------------------

	/* is unsigned integral */
	template <class T>
	concept is_unsigned_integral = requires {
		// check if T is integral
		requires xns::is_integral<T>;
		// check if T is unsigned
		requires T(-1) > T(0);
	};


}

#endif
