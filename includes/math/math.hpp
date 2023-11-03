#ifndef XNS_MATH_HEADER
#define XNS_MATH_HEADER

#include "is_arithmetic.hpp"
#include "is_floating.hpp"
#include "is_signed.hpp"
#include "numeric_limits.hpp"
#include "is_scalar.hpp"
#include "is_comparable.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E M A P -----------------------------------------------------------

	template <typename T>
	inline auto remap(T value, T oldmin, T oldmax, T newmin, T newmax) -> T {
		// assert that T is a floating point type
		static_assert(xns::is_floating<T>, "): T MUST BE FLOATING POINT :(");
		return (((value - oldmin) / (oldmax - oldmin)) * (newmax - newmin)) + newmin;
	}


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

	template <typename T>
	inline constexpr auto max(const T& a, const T& b) -> const T& {
		// assert that T and U are comparable types
		static_assert(xns::is_comparable<T>, "): MAX: TYPES MUST BE COMPARABLE :(");
		// return max value
		return a > b ? a : b;
	}

	// -- M I N ---------------------------------------------------------------

	template <typename T>
	inline constexpr auto min(const T& a, const T& b) -> const T& {
		// assert that T and U are comparable types
		static_assert(xns::is_comparable<T>, "): MIN: TYPES MUST BE COMPARABLE :(");
		// return min value
		return a < b ? a : b;
	}

	// -- C L A M P -----------------------------------------------------------

	template <typename T>
	inline constexpr auto clamp(const T& value, const T& min, const T& max) -> T {
		// assert that T and U are comparable types
		static_assert(xns::is_comparable<T>, "): CLAMP: TYPES MUST BE COMPARABLE :(");
		// return clamped value
		return value < min ? min : value > max ? max : value;
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
