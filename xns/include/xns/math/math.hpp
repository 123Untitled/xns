#ifndef MATH_HEADER
#define MATH_HEADER

#include "is_arithmetic.hpp"
#include "is_signed.hpp"
#include "numeric_limits.hpp"
#include "is_scalar.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A B S ---------------------------------------------------------------

	template <class T>
	constexpr T abs(const T& value) {

		// assert that T is an scalar type
		static_assert(xns::is_scalar<T>, "): T MUST BE SCALAR :(");

		// check T is floating point
		if constexpr (xns::is_floating<T>) {
			// return absolute value
			return value < 0 ? -value : value;
		}
		// check T is signed
		if constexpr (xns::is_signed<T>) {
			// check value is negative
			if (value < 0) {
				// check for overflow
				if (value == xns::limits::min<T>()) {
					// return max value of T
					return xns::limits::max<T>();
				}
				// return absolute value
				return -value;
			}
		}
		return value;

	}


	// -- M A X ---------------------------------------------------------------

	template <class T, class U>
	constexpr auto max(const T& a, const U& b) -> decltype(a > b ? a : b)& {

		// assert that T and U are scalar types
		static_assert(xns::is_scalar<T> && xns::is_scalar<U>, "): TYPES MUST BE SCALAR :(");

		// return max value
		return a > b ? a : b;
	}


	// -- M I N ---------------------------------------------------------------

	template <class T, class U>
	constexpr auto min(const T& a, const U& b) -> decltype(a < b ? a : b)& {

		// assert that T and U are scalar types
		static_assert(xns::is_scalar<T> && xns::is_scalar<U>, "): TYPES MUST BE SCALAR :(");

		// return min value
		return a < b ? a : b;
	}


	// -- C E I L -------------------------------------------------------------

	template <class T>
	constexpr T ceil(const T& value) {

		// assert that T is an floating point type
		static_assert(xns::is_floating<T>, "): T MUST BE FLOATING POINT :(");

		// check sign
		return value > 0 ? static_cast<T>(static_cast<xns::umax>(value)) + 1
						 : static_cast<T>(static_cast<xns::smax>(value));
	}


	// -- F L O O R -----------------------------------------------------------

	template <class T>
	constexpr T floor(const T& value) {

		// assert that T is an floating point type
		static_assert(xns::is_floating<T>, "): T MUST BE FLOATING POINT :(");

		// check sign
		return value > 0 ? static_cast<T>(static_cast<xns::umax>(value))
						 : static_cast<T>(static_cast<xns::smax>(value)) - 1;
	}



}

#endif
