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

#ifndef XNS_NUMERIC_LIMITS_HEADER
#define XNS_NUMERIC_LIMITS_HEADER

#include "other/base.hpp"

#include "type_traits/types.hpp"

#include "type_traits/type_categories/is_integral.hpp"
#include "type_traits/type_categories/is_scalar.hpp"
#include "type_traits/type_properties/is_signed.hpp"
#include "type_traits/type_properties/is_unsigned.hpp"

//#include "remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	template <typename T>
	class limits final {


		// -- assertions ------------------------------------------------------

		/* assert that T is an scalar type */
		static_assert(xns::is_scalar<T>, "limits: T must be an integral type");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::limits<T>;


			// -- public static methods ---------------------------------------

			/* max */
			static consteval auto max(void) -> T {

				if constexpr (xns::is_same<T, bool>)
					return true;

				else if constexpr (xns::is_floating_point<T>) {

					if constexpr (sizeof(T) == 4)
						// return IEEE 754 single precision max
						return 0x1.fffffep+127f;

					else if constexpr (sizeof(T) == 8)
						// return IEEE 754 double precision max
						return 0x1.fffffffffffffp+1023;
				}

				else {

					// number of bits in type
					constexpr T bits = static_cast<T>((sizeof(T) * 8) - xns::is_signed<T>);

					T count = 0;

					// loop through bits
					for (T i = 0; i < bits; ++i)
						// add shifted bit to max
						count |= static_cast<T>(static_cast<T>(1) << i);

					return count;
				}
			}

			/* min */
			static consteval auto min(void) -> T {

				if constexpr (xns::is_same<T, bool>)
					return false;

				else if constexpr (xns::is_floating_point<T>) {

					if constexpr (sizeof(T) == 4)
						// return IEEE 754 single precision min
						return -0x1.fffffep+127f;

					else if constexpr (sizeof(T) == 8)
						// return IEEE 754 double precision min
						return -0x1.fffffffffffffp+1023;
				}
				else {
					T max = self::max();
					return ~max;
				}
			}

			/* max number of digits */
			template <xns::is_base B = xns::dec>
			static consteval auto digits(void) -> decltype(sizeof(0)) {

				// max value of type
				auto limit = self::max();

				// number of digits
				decltype(sizeof(0)) digits = 0;

				do { // increment digits
					++digits;
					// divide max by base
				} while (limit /= B::base);

				return digits;
			}

			/* compile time max number of digits */
			//template <T N, xns::is_base B> requires (xns::is_integral<T>)
			//static consteval xns::umax digits(void) {
			//
			//	decltype(N) num = N;
			//
			//	// number of digits
			//	xns::size_t digits = 0;
			//
			//	// increment digits
			//	do { ++digits;
			//		// divide num by base
			//	} while (num /= B::base);
			//
			//	// return digits
			//	return digits;
			//}
			//
			//template <T N, xns::is_base B> requires (xns::is_floating<T>)
			//static consteval xns::umax digits(void) {
			//
			//
			//	return 0;
			//}




			template <typename U>
			static inline auto in_range(const U& value) -> bool {

				// check types are integral
				static_assert(xns::is_integral<U>, "in_range: type must be integral");

				constexpr auto min = self::min();
				constexpr auto max = self::max();


				// remove: comparison of integers of different signs: warning
				return (T)value >= (T)min && (T)value <= (T)max;
			}


	};


}

#endif
