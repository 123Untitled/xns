#ifndef IS_INTEGRAL_HEADER
#define IS_INTEGRAL_HEADER

#include "types.hpp"
#include "has_type.hpp"
#include "remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  I N T E G R A L ------------------------------------------------

	/* is integral concept */
	template <class T>
	concept is_integral = has_type<xns::remove_cv<T>,

		bool, char, short, int, long, long long,
		char8_t, wchar_t, char32_t, char16_t,
		signed char, unsigned char, unsigned short,
		unsigned int, unsigned long, unsigned long long>;


}


#endif
