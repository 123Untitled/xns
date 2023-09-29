#ifndef XNS_INTEGER_COMPARAISON_HEADER
#define XNS_INTEGER_COMPARAISON_HEADER

#include "is_integral.hpp"
#include "is_signed.hpp"
#include "is_unsigned.hpp"
#include "conditional.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	template <typename T, typename U>
	using smaller = xns::conditional<(sizeof(T) < sizeof(U)), T, U>;

	template <typename T, typename U>
	using larger = xns::conditional<(sizeof(T) > sizeof(U)), T, U>;


	// -- C O M P A R A I S O N -----------------------------------------------


	// -- E Q U A L I T Y -----------------------------------------------------

	// -- same sign equality --------------------------------------------------

	/* equality */
	template <xns::is_integral L,
			  xns::is_integral R> requires ((xns::is_unsigned<L> and xns::is_unsigned<R>) or
											(xns::is_signed<L>   and xns::is_signed<R>))
	inline constexpr auto equality(const L& left, const R& right) noexcept -> bool {
		using safe = xns::larger<L, R>;
		return static_cast<safe>(left) == static_cast<safe>(right);
	}


	// -- different sign equality ---------------------------------------------

	/* equality */
	template <xns::is_signed_integral S,
			  xns::is_unsigned_integral U>
	inline constexpr auto equality(const S& sign, const U& unsign) noexcept -> bool {

		if constexpr (sizeof(S) > sizeof(U)) {
			// case ex: signed int == unsigned char
			return sign == static_cast<S>(unsign);
		}
		// case ex: signed char == unsigned int
		//          signed char == unsigned char
		return sign < 0 ? false
			: static_cast<U>(sign) == unsign;
	}

	/* equality */
	template <xns::is_unsigned_integral U,
			  xns::is_signed_integral S>
	inline constexpr auto equality(const U& left, const S& right) noexcept -> bool {
		return equality(right, left);
	}



	// -- L E S S  T H A N ----------------------------------------------------

	// -- same sign less than -------------------------------------------------

	/* less than */
	template <xns::is_integral L,
			  xns::is_integral R> requires ((xns::is_unsigned<L> and xns::is_unsigned<R>) or
											(xns::is_signed<L>   and xns::is_signed<R>))
	inline constexpr auto less_than(const L& left, const R& right) noexcept -> bool {
		using safe = xns::larger<L, R>;
		return static_cast<safe>(left) < static_cast<safe>(right);
	}


	// -- different sign less than --------------------------------------------

	/* less than */
	template <xns::is_signed_integral S,
			  xns::is_unsigned_integral U>
	inline constexpr auto less_than(const S& sign, const U& unsign) noexcept -> bool {

		if constexpr (sizeof(S) > sizeof(U)) {
			// case ex: signed int < unsigned char
			return sign < static_cast<S>(unsign);
		}
		// case ex: signed char < unsigned int
		//          signed char < unsigned char
		return sign < 0 ? true
			: static_cast<U>(sign) < unsign;
	}

	/* less than */
	template <xns::is_unsigned_integral U,
			  xns::is_signed_integral S>
	inline constexpr auto less_than(const U& left, const S& right) noexcept -> bool {
		return less_than(right, left);
	}







}

#endif
