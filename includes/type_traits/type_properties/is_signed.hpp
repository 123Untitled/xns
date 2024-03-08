#ifndef XNS_IS_SIGNED_HEADER
#define XNS_IS_SIGNED_HEADER

#include "is_integral.hpp"
#include "is_arithmetic.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  S I G N E D ----------------------------------------------------

	/* is signed */
	template <class T>
	concept is_signed = xns::is_arithmetic<T> and (static_cast<T>(-1) < static_cast<T>(0));


	// -- I S  S I G N E D  I N T E G R A L -----------------------------------

	/* is signed integral */
	template <class T>
	concept is_signed_integral = xns::is_integral<T> and xns::is_signed<T>;

} // namespace xns

#endif // XNS_IS_SIGNED_HEADER
