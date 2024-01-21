#ifndef XNS_IS_INTEGRAL_HEADER
#define XNS_IS_INTEGRAL_HEADER

#include "is_one_of.hpp"
#include "remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  I N T E G R A L ------------------------------------------------

	/* is integral concept */
	template <class T>
	concept is_integral = xns::is_one_of<xns::remove_cv<T>,

		bool, char, short, int, long, long long,
		char8_t, char32_t, char16_t, wchar_t,
		signed char, unsigned char, unsigned short,
		unsigned int, unsigned long, unsigned long long>;


}


#endif
