#ifndef RATIO_HEADER
#define RATIO_HEADER

#include "types.hpp"
#include "macro.hpp"
#include "is_same.hpp"

#include "is_integral.hpp"
#include "is_signed.hpp"
#include "is_unsigned.hpp"
#include "numeric_limits.hpp"
#include "integral_constant.hpp"
#include "integral.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R A T I O  C L A S S ------------------------------------------------

	template <xns::umax N, xns::umax D = 1>
	class ratio final {


		// -- assertions ------------------------------------------------------

		/* check denominator is not zero */
		static_assert(D != 0, "): DENOMINATOR CANNOT BE ZERO :(");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::ratio<N, D>;

			/* size type */
			using size_type = decltype(N);


			// -- public static constants -------------------------------------

			/* numerator */
			static constexpr size_type num = N;

			/* denominator */
			static constexpr size_type den = D;


			// -- public constructors -----------------------------------------

			/* non-instanciable class */
			NON_INSTANCIABLE(ratio);


			// -- public accessors --------------------------------------------

			/* numerator */
			static inline consteval size_type numerator(void) {
				// return numerator
				return _num;
			}

			/* denominator */
			static inline consteval size_type denominator(void) {
				// return denominator
				return _den;
			}


		private:

			// -- private static methods --------------------------------------

			/* greatest common divisor */
			static consteval size_type gcd(const size_type a, const size_type b) {
				// return recursive gcd
				return b == 0 ? a : gcd(b, a % b);
			}

			/* absolute value */
			static consteval size_type abs(const size_type a) {
				// return absolute value
				return a < 0 ? -a : a;
			}

			/* sign */
			static consteval size_type sign(const size_type a) {
				// return sign
				return (a > 0) - (a < 0);
			}


			// -- private constants -------------------------------------------

			/* numerator */
			static constexpr size_type _num = (sign(den) * num) / gcd(num, den);

			/* denominator */
			static constexpr size_type _den = abs(den) / gcd(num, den);




	};


	// -- I S  R A T I O ------------------------------------------------------

	/* is ratio concept */
	template <class T>
	concept is_ratio = xns::is_same<T, xns::ratio<T::num, T::den>>;


	// -- R A T I O  C O M P A R I S O N --------------------------------------

	// -- detail --------------------------------------------------------------

	namespace impl {

		/* equal */
		template <xns::is_ratio R1, xns::is_ratio R2>
		struct ratio_equal final
		: public xns::bool_constant<(R1::num == R2::num) && (R1::den == R2::den)> {};

		/* not equal */
		template <xns::is_ratio R1, xns::is_ratio R2>
		struct ratio_not_equal final
		: public xns::bool_constant<!ratio_equal<R1, R2>::value> {};

		/* less */
		template <xns::is_ratio R1, xns::is_ratio R2>
		struct ratio_less final
		: public xns::bool_constant<(R1::num * R2::den < R2::num * R1::den)> {};

		/* less equal */
		template <xns::is_ratio R1, xns::is_ratio R2>
		struct ratio_less_equal final
		: public xns::bool_constant<ratio_less<R1, R2>::value || ratio_equal<R1, R2>::value> {};

		/* greater */
		template <xns::is_ratio R1, xns::is_ratio R2>
		struct ratio_greater final
		: public xns::bool_constant<!ratio_less_equal<R1, R2>::value> {};

		/* greater equal */
		template <xns::is_ratio R1, xns::is_ratio R2>
		struct ratio_greater_equal final
		: public xns::bool_constant<!ratio_less<R1, R2>::value> {};


	}

	/* equal */
	template <class R1, class R2>
	concept ratio_equal = xns::impl::ratio_equal<R1, R2>::value;

	/* not equal */
	template <class R1, class R2>
	concept ratio_not_equal = xns::impl::ratio_not_equal<R1, R2>::value;

	/* less */
	template <class R1, class R2>
	concept ratio_less = xns::impl::ratio_less<R1, R2>::value;

	/* less equal */
	template <class R1, class R2>
	concept ratio_less_equal = xns::impl::ratio_less_equal<R1, R2>::value;

	/* greater */
	template <class R1, class R2>
	concept ratio_greater = xns::impl::ratio_greater<R1, R2>::value;

	/* greater equal */
	template <class R1, class R2>
	concept ratio_greater_equal = xns::impl::ratio_greater_equal<R1, R2>::value;


	// -- C O N V E R S I O N  F A C T O R ------------------------------------

	/* ratio conversion factor */
	template <xns::is_ratio R1, xns::is_ratio R2>
	consteval xns::umax ratio_conversion_factor(void) {


		if constexpr      (xns::ratio_less<R1, R2>) {

			return static_cast<xns::umax>(R2::num * R1::den) /
				   static_cast<xns::umax>(R2::den * R1::num);
		}

		else if constexpr (xns::ratio_greater<R1, R2>) {

			return static_cast<xns::umax>(R1::num * R2::den) /
				   static_cast<xns::umax>(R1::den * R2::num);
		}

		return 1.0;

		// return conversion factor
		//return R1::num * R2::den / R1::den * R2::num;
		// NEED TO CHECK OVERFLOW !!!
	}


	// -- R A T I O  A L I A S E S --------------------------------------------

	/* yocto */ // integer not representable

	/* zepto */ // integer not representable

	/* atto */
	using atto  = xns::ratio<1, 1'000'000'000'000'000'000>;

	/* femto */
	using femto = xns::ratio<1, 1'000'000'000'000'000>;

	/* pico */
	using pico  = xns::ratio<1, 1'000'000'000'000>;

	/* nano */
	using nano  = xns::ratio<1, 1'000'000'000>;

	/* micro */
	using micro = xns::ratio<1, 1'000'000>;

	/* milli */
	using milli = xns::ratio<1, 1'000>;

	/* centi */
	using centi = xns::ratio<1, 100>;

	/* deci */
	using deci  = xns::ratio<1, 10>;

	/* deca */
	using deca  = xns::ratio<10, 1>;

	/* hecto */
	using hecto = xns::ratio<100, 1>;

	/* kilo */
	using kilo  = xns::ratio<1'000, 1>;

	/* mega */
	using mega  = xns::ratio<1'000'000, 1>;

	/* giga */
	using giga  = xns::ratio<1'000'000'000, 1>;

	/* tera */
	using tera  = xns::ratio<1'000'000'000'000, 1>;

	/* peta */
	using peta  = xns::ratio<1'000'000'000'000'000, 1>;

	/* exa */
	using exa   = xns::ratio<1'000'000'000'000'000'000, 1>;

	/* zetta */ // integer not representable

	/* yotta */ // integer not representable



	// -- compile-time safe multiplication ------------------------------------

	/* multiply two integers */
	template <auto a, auto b> requires (xns::is_signed<decltype(a)> || xns::is_signed<decltype(b)>)
	consteval auto multiply(void) {


		/*
		constexpr bool overflow = (b != 0) && (a < (xns::min<xns::smax>() / b));

		// check for overflow
		static_assert(!overflow, "): MULTIPLICATION OVERFLOW :(");

		// return multiplication
		return static_cast<xns::smax>(a) * static_cast<xns::smax>(b);
		*/


	}

	template <auto a, auto b> requires (xns::is_unsigned<decltype(a)> && xns::is_unsigned<decltype(b)>)
	consteval auto multiply(void) {

		// unsigned case

		constexpr bool overflow = (b != 0) && (a > (xns::limits::max<xns::umax>() / b));

		// check for overflow
		static_assert(!overflow, "): MULTIPLICATION OVERFLOW :(");

		// return multiplication
		return static_cast<xns::umax>(
					static_cast<xns::umax>(a) *
					static_cast<xns::umax>(b)
		);

	}


	consteval inline auto testmulti(void) {

		constexpr xns::umax a = xns::limits::max<xns::umax>();
		constexpr xns::smax b = 1;

		//xns::integral c{2};

		return multiply<a, b>();
	}


}

#endif
