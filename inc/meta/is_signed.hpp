#ifndef IS_SIGNED_HEADER
#define IS_SIGNED_HEADER

#include "is_integral.hpp"
#include "is_arithmetic.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace xns {


	// -- I S  S I G N E D ----------------------------------------------------

	/* is signed */
	template <class T>
	concept is_signed = requires {
		// check if T is arithmetic
		requires xns::is_arithmetic<T>;
		// check if T is signed
		requires T(-1) < T(0);
	};


	// -- I S  S I G N E D  I N T E G R A L -----------------------------------

	/* is signed integral */
	template <class T>
	concept is_signed_integral = requires {
		// check if T is integral
		requires xns::is_integral<T>;
		// check if T is signed
		requires T(-1) < T(0);
	};


}

#endif
