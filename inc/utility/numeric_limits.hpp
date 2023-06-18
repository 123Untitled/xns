#ifndef NUMERIC_LIMIT_HPP
#define NUMERIC_LIMIT_HPP

#include "base.hpp"

#include "types.hpp"

#include "is_integral.hpp"
#include "is_signed.hpp"
#include "is_unsigned.hpp"
#include "remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	class limits final {


		public:

			// -- public static methods ---------------------------------------

			/* max */
			template <xns::is_integral T> requires xns::is_not_same<T, bool>
			static consteval xns::remove_cvr<T> max(void) {
				// remove const volatile reference
				using type = xns::remove_cvr<T>;
				// number of bits in type
				constexpr type bits = (sizeof(type) * 8) - xns::is_signed<type>;
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
			template <xns::is_integral T> requires xns::is_not_same<T, bool>
			static consteval xns::remove_cvr<T> min(void) {
				// return inverse of max
				return ~max<T>();
			}

			/* max for bool */
			template <class T> requires xns::is_same<T, bool>
			static consteval auto max(void) {
				return true;
			}

			/* min for bool */
			template <class T> requires xns::is_same<T, bool>
			static consteval auto min(void) {
				return false;
			}

			/* max for floating */
			template <xns::is_floating T>
			static consteval auto max(void) {
				return 0;
			}

			/* min for floating */
			template <xns::is_floating T>
			static consteval auto min(void) {
				return 0;
			}


			/* max number of digits */
			template <xns::is_integral T, xns::is_base B = xns::dec>
			static consteval xns::umax digits(void) {

				// max value of type
				auto type_max = max<T>();

				// number of digits
				xns::umax digits = 0;

				do { // increment digits
					++digits;
					// divide max by 10
				} while (type_max /= B::base);

				// return digits
				return digits;
			}

			/* compile time max number of digits */
			template <auto N, xns::is_base B>
			static consteval xns::umax digits(void) {

				static_assert(xns::is_integral<decltype(N)>, "): N MUST BE INTEGRAL :(");

				decltype(N) num = N;

				// number of digits
				xns::size_t digits = 0;

				// increment digits
				do { ++digits;
					// divide num by base
				} while (num /= B::base);

				// return digits
				return digits;
			}


	};


}

#endif
