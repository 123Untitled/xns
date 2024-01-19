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
		return oldmin == oldmax ? newmin : (((value - oldmin) / (oldmax - oldmin)) * (newmax - newmin)) + newmin;
	}


	// -- D I F F -------------------------------------------------------------

	template <typename T>
	inline auto diff(const T& a, const T& b) -> T {
		// assert that T and U are comparable types
		static_assert(xns::is_scalar<T>, "): DIFF: types must be scalar :(");
		// return difference
		return a > b ? a - b : b - a;
	}


	// -- A B S ---------------------------------------------------------------

	template <typename T>
	constexpr auto abs(const T& value) noexcept -> T {

		// assert that T is an scalar type
		static_assert(xns::is_scalar<T>, "): ABS: types must be scalar :(");

		// check T is floating point
		if constexpr (xns::is_floating<T>) {
			// return absolute value
			return value < 0 ? -value : value;
		}
		// check T is signed
		if constexpr (xns::is_signed<T>) {
			// return absolute value
			return value < 0 ? value == xns::limits::min<T>()
									  ? xns::limits::max<T>()
									  : -value
									  :  value;
		}
		else {
			return value;
		}

	}


	// -- M A X ---------------------------------------------------------------

	template <typename T>
	inline constexpr auto max(const T& a, const T& b) -> const T& {
		// assert that T and U are comparable types
		static_assert(xns::is_comparable<T>, "): MAX: types must be comparable :(");
		// return max value
		return a > b ? a : b;
	}


	// -- M I N ---------------------------------------------------------------

	template <typename T>
	inline constexpr auto min(const T& a, const T& b) -> const T& {
		// assert that T and U are comparable types
		static_assert(xns::is_comparable<T>, "): MIN: types must be comparable :(");
		// return min value
		return a < b ? a : b;
	}


	// -- C L A M P -----------------------------------------------------------

	template <typename T>
	inline constexpr auto clamp(const T& value, const T& min, const T& max) -> T {
		// assert that T and U are comparable types
		static_assert(xns::is_comparable<T>, "): CLAMP: types must be comparable :(");
		// return clamped value
		return value < min ? min : value > max ? max : value;
	}


	// -- C E I L -------------------------------------------------------------

	template <typename T>
	constexpr auto ceil(const T& value) noexcept -> T {
		// assert that T is an floating point type
		static_assert(xns::is_floating<T>, "): CEIL: T must be a floating point type :(");
		// check sign
		return value > 0 ? static_cast<T>(static_cast<xns::umax>(value)) + 1
						 : static_cast<T>(static_cast<xns::smax>(value));
	}


	// -- F L O O R -----------------------------------------------------------

	template <typename T>
	constexpr auto floor(const T& value) noexcept -> T {
		// assert that T is an floating point type
		static_assert(xns::is_floating<T>, "): FLOOR: T must be a floating point type :(");
		// check sign
		return value > 0 ? static_cast<T>(static_cast<xns::umax>(value))
						 : static_cast<T>(static_cast<xns::smax>(value)) - 1;
	}


	// -- T O  R A D I A N S --------------------------------------------------

	/* convert degrees to radians */
	template <typename T>
	auto to_radians(const T& degrees) noexcept -> T {
		return degrees * 0.01745329251994329576923690768489;
	}

	/* convert radians to degrees */
	template <typename T>
	auto to_degrees(const T& radians) noexcept -> T {
		return radians * 57.295779513082320876798154814105;
	}


	template <typename T>
	auto sqrt(const T& value) noexcept -> T {

		if (value <= 0) return 0;
		double tol = 1e-6;  // Tolérance pour la précision de la racine carrée
		double guess = value;
		double diff = 1;

		while (diff > tol) {
			double newGuess = (guess + value / guess) / 2;
			diff = abs(newGuess - guess);
			guess = newGuess;
		}
		return guess;
	}

	template <typename T, typename E>
	auto pow(const T& value, const E& exponent) noexcept -> T {
		static_assert(xns::is_arithmetic<T>, "): POW: T must be an arithmetic type :(");
		static_assert(xns::is_integral<E>,   "): POW: E must be an integral type :(");
		if (exponent == 0) return 1;
		if (exponent == 1) return value;
		T result = value;
		for (T i = 1; i < exponent; ++i)
			result *= value;
		return result;
	}

	template <typename T>
	auto cos(const T& value) noexcept -> T {
		T x = value;
		x *= 0.15915494309189535;
		x -= 0.25  +  xns::floor(x + 0.25);
		x *= 16.0  * (xns::abs(x) - 0.5);
//#if EXTENDED_PRECISION
		x += 0.225 * x * (xns::abs(x) - 1.0);
//#endif
		return x;
	}

	template <typename T>
	auto sin(const T& value) noexcept -> T {
		return xns::cos(value - 1.5707963267948966);
	}

	template <typename T>
	auto tan(const T& value) noexcept -> T {
		return xns::sin(value) / xns::cos(value);
	}





	template <typename T>
	class min_max final {

		// -- assertions ------------------------------------------------------

		/* comparable type */
		static_assert(xns::is_comparable<T>, "): MIN_MAX: types must be comparable :(");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::min_max<T>;

			/* value type */
			using value_type = T;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline constexpr min_max(void) noexcept
			: _min{xns::limits::max<T>()}, _max{xns::limits::min<T>()} {}

			/* copy constructor */
			inline constexpr min_max(const self& other) noexcept
			: _min{other._min}, _max{other._max} {}

			/* move constructor */
			inline constexpr min_max(self&& other) noexcept
			: self{other} {}

			/* destructor */
			inline ~min_max(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			inline constexpr auto operator=(const self& other) noexcept -> self& {
				// copy values
				_min = other._min;
				_max = other._max;
				// return self reference
				return *this;
			}

			/* move assignment operator */
			inline constexpr auto operator=(self&& other) noexcept -> self& {
				return self::operator=(other);
			}


			// -- public modifiers --------------------------------------------

			/* update min and max values */
			inline constexpr auto update(const value_type& value) noexcept -> void {
				// update min value
				_min = xns::min(_min, value);
				// update max value
				_max = xns::max(_max, value);
			}


			// -- public accessors --------------------------------------------

			/* min value */
			inline constexpr auto min(void) const noexcept -> const value_type& {
				return _min;
			}

			/* max value */
			inline constexpr auto max(void) const noexcept -> const value_type& {
				return _max;
			}


		private:

			// -- private members ---------------------------------------------

			/* min value */
			value_type _min;

			/* max value */
			value_type _max;

	};









}

#endif
