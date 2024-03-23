/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_INTEGER_ARITHMETIC_HEADER
#define XNS_INTEGER_ARITHMETIC_HEADER

// local headers
#include "xns/utility/numeric_limits.hpp"
#include "xns/type_traits/type_categories/is_integral.hpp"
#include "xns/type_traits/type_properties/is_signed.hpp"
#include "xns/type_traits/type_properties/is_unsigned.hpp"
#include "xns/type_traits/types.hpp"

// T = L = R

// T < R < L
// T < L < R // inverse call
// L < R < T
// R < L < T // inverse call
// L < T < R
// R < T < L // inverse call

// T < L = R
// L = R < T
// L < T = R
// T = R < L
// R < L = T
// L = T < R


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// safe arithmetic operations (no overflow/underflow), clamp to min/max if necessary


	template <typename T, typename L, typename R>
	struct arithmetic final {

		// -- assertions ------------------------------------------------------

		/* require integral types */
		static_assert(xns::is_integral<T> and
					  xns::is_integral<L> and
					  xns::is_integral<R>, "): ARITHMETIC: T, L, R must be integral types! :(");


		// -- public types ----------------------------------------------------

		/* self type */
		using self = arithmetic<T, L, R>;


		// -- permutations ----------------------------------------------------

		enum : bool {

			// T = L = R
			T_EQUAL_L_EQUAL_R = (sizeof(T) == sizeof(L) && sizeof(L) == sizeof(R)),

			// T < R < L
			T_LESS_R_LESS_L   = (sizeof(T) <  sizeof(R) && sizeof(R) <  sizeof(L)),

			// T < L < R // inverse call
			T_LESS_L_LESS_R   = (sizeof(T) <  sizeof(L) && sizeof(L) <  sizeof(R)),

			// L < R < T
			L_LESS_R_LESS_T   = (sizeof(L) <  sizeof(R) && sizeof(R) <  sizeof(T)),

			// R < L < T // inverse call
			R_LESS_L_LESS_T   = (sizeof(R) <  sizeof(L) && sizeof(L) <  sizeof(T)),

			// L < T < R
			L_LESS_T_LESS_R   = (sizeof(L) <  sizeof(T) && sizeof(T) <  sizeof(R)),

			// R < T < L // inverse call
			R_LESS_T_LESS_L   = (sizeof(R) <  sizeof(T) && sizeof(T) <  sizeof(L)),

			// T < L = R
			T_LESS_L_EQUAL_R  = (sizeof(T) <  sizeof(L) && sizeof(L) == sizeof(R)),

			// L = R < T
			L_EQUAL_R_LESS_T  = (sizeof(L) == sizeof(R) && sizeof(R) <  sizeof(T)),

			// L < T = R
			L_LESS_T_EQUAL_R  = (sizeof(L) <  sizeof(T) && sizeof(T) == sizeof(R)),

			// T = R < L
			T_EQUAL_R_LESS_L  = (sizeof(T) == sizeof(R) && sizeof(R) <  sizeof(L)),

			// R < L = T
			R_LESS_L_EQUAL_T  = (sizeof(R) <  sizeof(L) && sizeof(L) == sizeof(T)),

			// L = T < R
			L_EQUAL_T_LESS_R  = (sizeof(L) == sizeof(T) && sizeof(T) <  sizeof(R))

		};



		// only_unsigned
		static constexpr bool only_unsigned = (xns::is_unsigned<T> and
											   xns::is_unsigned<L> and
											   xns::is_unsigned<R>);

		// only_signed
		static constexpr bool only_signed = (xns::is_signed<T> and
											 xns::is_signed<L> and
											 xns::is_signed<R>);

		// mixed_sign
		static constexpr bool mixed_sign = (not only_unsigned and
											not only_signed);


		// -- addition --------------------------------------------------------

		/* addition */ // [only_unsigned] T = L = R
		static inline constexpr auto addition(const L& lhs, const R& rhs) noexcept -> T
			requires (only_unsigned and T_EQUAL_L_EQUAL_R == true) {
			// overflow check
			return (lhs > (xns::limits<T>::max() - rhs))
					? xns::limits<T>::max() : (lhs + rhs);
		}

		/* addition */ // [only_unsigned] T < R < L
		static inline constexpr auto addition(const L& lhs, const R& rhs) noexcept -> T
			requires (only_unsigned and T_LESS_R_LESS_L == true) {
			// compute calcul into larger type
			L tmp = (rhs > xns::limits<L>::max() - lhs)
				    ? xns::limits<L>::max() : lhs + static_cast<L>(rhs);
			// overflow check
			return (tmp > xns::limits<R>::max())
				    ? xns::limits<T>::max() : static_cast<T>(tmp);
		}

		/* addition */ // [only_unsigned] T < L < R // inverse call
		static inline constexpr auto addition(const L& lhs, const R& rhs) noexcept -> T
			requires (only_unsigned and T_LESS_L_LESS_R == true) {
			// return inverse call
			return xns::arithmetic<T, R, L>::addition(rhs, lhs);
		}


		/* addition */ // [only_unsigned] L < R < T or R < L < T
		static inline constexpr auto addition(const L& lhs, const R& rhs) noexcept -> T
			requires (only_unsigned and (L_LESS_R_LESS_T == true or R_LESS_L_LESS_T == true)) {
			// no risk of overflow
			return static_cast<T>(lhs) + static_cast<T>(rhs);
		}


		/* addition */ // [only_unsigned] L < T < R
		static inline constexpr auto addition(const L& lhs, const R& rhs) noexcept -> T
			requires (only_unsigned and L_LESS_T_LESS_R == true) {
			// get lhs into result type
			T tmp = static_cast<T>(lhs);

			tmp = (rhs > xns::limits<T>::max() - tmp)
				    ? xns::limits<T>::max() : tmp + static_cast<T>(rhs);
			return tmp;
		}

		/* addition */ // [only_unsigned] R < T < L // inverse call
		static inline constexpr auto addition(const L& lhs, const R& rhs) noexcept -> T
			requires (only_unsigned and R_LESS_T_LESS_L == true) {
			// return inverse call
			return xns::arithmetic<T, R, L>::addition(rhs, lhs);
		}



		/* addition */ // [only_unsigned] T < L = R
		static inline constexpr auto addition(const L& lhs, const R& rhs) noexcept -> T
			requires (only_unsigned and T_LESS_L_EQUAL_R == true) {
			return T{};
		}

		/* addition */ // [only_unsigned] L = R < T
		static inline constexpr auto addition(const L& lhs, const R& rhs) noexcept -> T
			requires (only_unsigned and L_EQUAL_R_LESS_T == true) {
			// no risk of overflow
			return static_cast<T>(lhs) + static_cast<T>(rhs);
		}

		/* addition */ // [only_unsigned] L < T = R
		static inline constexpr auto addition(const L& lhs, const R& rhs) noexcept -> T
			requires (only_unsigned and L_LESS_T_EQUAL_R == true) {
			return arithmetic<T, R, R>::addition(static_cast<R>(lhs), rhs);
		}

		/* addition */ // [only_unsigned] T = R < L
		static inline constexpr auto addition(const L& lhs, const R& rhs) noexcept -> T
			requires (only_unsigned and T_EQUAL_R_LESS_L == true) {
			// implementation...
			return T{};
		}

		/* addition */ // [only_unsigned] R < L = T
		static inline constexpr auto addition(const L& lhs, const R& rhs) noexcept -> T
			requires (only_unsigned and R_LESS_L_EQUAL_T == true) {
			// implementation...
			return T{};
		}

		/* addition */ // [only_unsigned] L = T < R
		static inline constexpr auto addition(const L& lhs, const R& rhs) noexcept -> T
			requires (only_unsigned and L_EQUAL_T_LESS_R == true) {
			// implementation...
			return T{};
		}






		///* addition */
		//static inline constexpr auto addition(const L& lhs, const R& rhs) noexcept -> T
		//	requires (only_signed) {
		//	// implementation...
		//	return T{};
		//}

		///* addition */
		//static inline constexpr auto addition(const L& lhs, const R& rhs) noexcept -> T
		//	requires (mixed_sign) {
		//	// implementation...
		//	return T{};
		//}


	};

}

#endif // INTEGER_ARITHMETIC_HEADER















// T < R < L
// T < L < R
// T < L = R
// T > L = R
// L < R < T
// L < T < R
// L < T = R
// L > T = R
// R < T < L
// R < L < T
// R < L = T
// R > L = T
// T = L = R


