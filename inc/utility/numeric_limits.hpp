#ifndef NUMERIC_LIMIT_HPP
#define NUMERIC_LIMIT_HPP

#include "type_traits.hpp"
#include "base.hpp"
#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- M I N  M A X --------------------------------------------------------

	/* max */
	template <Xf::integral_c T>
	consteval auto max(void) {
		// remove cv
		using type = Xf::remove_cv_t<T>;
		// number of bits in type
		constexpr type bits = (sizeof(type) * 8) - Xf::is_signed_v<type>;
		// max value of type
		type type_max = 0;
		// loop through bits
		for (type x = 0; x < bits; ++x) {
			// add shifted bit to max
			type_max += (static_cast<type>(1) << x);
		} // return max
		return type_max;
	}


	/* min */
	template <Xf::integral_c T>
	consteval auto min(void) {
		// inverse all bits
		return static_cast<T>(~max<T>());
	}

	// -- M A X  D I G I T S --------------------------------------------------

	// max number of digits in a type (base 10)
	template <Xf::integral_c T>
	consteval T max_digits(void) {
		// remove cv
		using type = Xf::remove_cv_t<T>;
		// max value of type
		type type_max = xns::max<type>();
		// number of digits
		type digits = 0;
		do { // increment digits
			++digits;
			// divide max by 10
		} while ((type_max /= 10));
		// return digits
		return digits;
	}

	// max number of digits in a type (base 10)
	template <Xf::integral_c T>
	consteval T min_digits(void) {
		// remove cv
		using type = Xf::remove_cv_t<T>;
		// min value of type
		type type_min = xns::min<type>();
		// number of digits
		type digits = 0;
		do { // increment digits
			++digits;
			// divide max by 10
		} while ((type_min /= 10));
		// return digits
		return digits;
	}



	template <Xf::is_base_c B, Xf::integral_c T>
	consteval SizeT static_digits(const T number) {
		// remove const and volatile
		using Type = Xf::remove_cv_t<T>;
		// instance of new type
		Type num = number;
		// number of digits
		SizeT digits = 0; // number < 0;
		// increment digits
		do { ++digits;
			// divide num by base
		} while ((num /= static_cast<Type>(B::base)));
		// return digits
		return digits;
	}




};

#endif
