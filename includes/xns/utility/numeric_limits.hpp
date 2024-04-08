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

#include "xns/other/base.hpp"

#include "xns/type_traits/types.hpp"

#include "xns/type_traits/type_categories/is_integral.hpp"
#include "xns/type_traits/type_categories/is_floating_point.hpp"
#include "xns/type_traits/type_categories/is_bool.hpp"
#include "xns/type_traits/type_categories/is_scalar.hpp"
#include "xns/type_traits/type_properties/is_signed.hpp"
#include "xns/type_traits/type_properties/is_unsigned.hpp"

//#include "xns/remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	template <typename ___type>
	class limits final {


		// -- assertions ------------------------------------------------------

		/* assert that ___type is an scalar type */
		static_assert(xns::is_scalar<___type>, "limits: ___type must be an integral type");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::limits<___type>;


			// -- public static methods ---------------------------------------

			/* max bool */
			static consteval auto max(void) noexcept -> ___type requires xns::is_bool<___type> {
				return true;
			}

			/* min bool */
			static consteval auto min(void) noexcept -> ___type requires xns::is_bool<___type> {
				return false;
			}


			/* max integral */
			static consteval auto max(void) noexcept -> ___type requires (xns::is_integral<___type>
																   && not xns::is_bool<___type>) {

				// number of bits in type
				constexpr ___type bits = static_cast<___type>((sizeof(___type) * xns::bits_per_byte) - xns::is_signed<___type>);

				___type count = 0;

				// loop through bits
				for (___type i = 0; i < bits; ++i)
					// add shifted bit to max
					count |= static_cast<___type>(static_cast<___type>(1) << i);

				return count;
			}

			/* min integral */
			static consteval auto min(void) noexcept -> ___type requires (xns::is_integral<___type>
																   && not xns::is_bool<___type>) {
				___type max = self::max();
				return ~max;
			}


			/* max floating point */
			static consteval auto max(void) noexcept -> ___type requires xns::is_floating_point<___type> {

				if constexpr (sizeof(___type) == 4)
					// return IEEE 754 single precision max
					return 0x1.fffffep+127f;

				else if constexpr (sizeof(___type) == 8)
					// return IEEE 754 double precision max
					return 0x1.fffffffffffffp+1023;
			}

			/* min floating point */
			static consteval auto min(void) noexcept -> ___type requires xns::is_floating_point<___type> {

				if constexpr (sizeof(___type) == 4)
					// return IEEE 754 single precision min
					return -0x1.fffffep+127f;

				else if constexpr (sizeof(___type) == 8)
					// return IEEE 754 double precision min
					return -0x1.fffffffffffffp+1023;
			}



			/* max number of digits */
			template <xns::is_base ___base = xns::dec>
			static consteval auto digits(void) -> decltype(sizeof(0)) {

				// max value of type
				auto ___lm = self::max();

				// number of digits
				decltype(sizeof(0)) digits = 0;

				do { // increment digits
					++digits;
					// divide max by base
				} while (___lm /= ___base::base);

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




			template <typename ___u>
			static auto in_range(const ___u& value) noexcept -> bool {

				// check types are integral
				static_assert(xns::is_integral<___u>, "in_range: type must be integral");

				constexpr auto min = self::min();
				constexpr auto max = self::max();


				// remove: comparison of integers of different signs: warning
				return (___type)value >= (___type)min && (___type)value <= (___type)max;
			}


	};


}

#endif
