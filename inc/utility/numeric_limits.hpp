#ifndef NUMERIC_LIMIT_HPP
#define NUMERIC_LIMIT_HPP

#include "type_traits.hpp"
#include <iostream>

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- M I N  M A X --------------------------------------------------------

	/* max */
	template <typename Type>
	constexpr Type max(void) {
		// number of bits in type
		constexpr Type bits = (sizeof(Type) * 8) - is_signed<Type>::value;
		// max value of type
		Type type_max = 0;
		// loop through bits
		for (Type x = 0; x < bits; ++x) {
			// add shifted bit to max
			type_max += (1 << x);
		} // return max
		return type_max;
	}

	/* min */
	template <typename Type>
	constexpr Type min(void) {
		Type type_min = ~max<Type>();
		//type_min = ~type_min;
		return type_min;
	}

	// -- M A X  D I G I T S --------------------------------------------------

	// max number of digits in a type (base 10)
	template <typename Type>
	constexpr Type max_digits(void) {
		// max value of type
		Type type_max = max<Type>();
		// number of digits
		Type digits = 0;
		// loop through digits
		while (type_max) {
			// divide max by 10
			type_max /= 10;
			// increment digits
			++digits;
		} // return digits
		return digits;
	}



};

#endif
