#ifndef CONVERSIONS_HEADER
#define CONVERSIONS_HEADER

#include "string.hpp"
#include "types.hpp"
#include "is_signed.hpp"
#include "numeric_limits.hpp"
#include "macro.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I N T E G E R  T O  S T R I N G -------------------------------------

	class conversion {

		public:

			// -- public constructors -----------------------------------------

			/* non-instanciable class */
			NON_INSTANCIABLE(conversion);


			// -- public static methods ---------------------------------------

			template <xns::is_signed N>
			static xns::string integer_to_string(N number) {
				xns::string str;

				str.reserve(xns::limits::digits<N>() + 1); // INFO: +1 for negative sign

				constexpr N type_min = xns::limits::min<N>();

				N base = 10;

				bool negative = false;

				xns::string::size_type x = 0;

				// check negative
				if (number < 0) {
					// set negative flag
					negative = true;

					if (number == type_min) {
						// INFO: this is a special case
					}
					else {
						// inverse number
						number = -number;
					}
				}

				do {
					N rem = number % base;
					//_str[x] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
					str._str[x] = (number % 10) + '0';
					++x;
				} while ((number /= base));

				if (negative) { str._str[x++] = '-'; }

				str._size_and_terminator(x);
				// reverse all characters
				str.reverse();

				return str;
			};


			template <xns::is_unsigned N>
			static xns::string integer_to_string(N number) {

				xns::string str;

				str.reserve(xns::limits::digits<N>());

				// declare size type
				xns::string::size_type x = 0;

				// loop through number
				do {
					str._str[x] = (number % 10) + '0';
					number /= 10;
					++x;
				} while (number);

				str._size_and_terminator(x);

				// reverse all characters
				str.reverse();

				return str;
			};


		template <xns::is_string S, is_integral I>
		static bool string_to_integer(const S& str, I& value) {

			/* integer type */
			using integer       = xns::remove_cvr<I>;
			/* string type */
			using string_type   = xns::remove_cvr<S>;
			/* size type */
			using size_type     = typename string_type::size_type;
			/* character type */
			using char_t        = typename string_type::char_t;
			/* const pointer */
			using const_pointer = typename string_type::const_pointer;


			//const_pointer ptr = str.pointer();

			// index
			size_type x = 0;
			// negative flag
			int negative = 1;
			// reset value
			value = 0;

			// skip leading whitespace
			while (x < str.size()
				&& xns::basic_string<char_t>::is_whitespace(str[x])) {
				++x;
			}

			// check for sign
			if      (str[x] == '+') { ++x;                }
			else if (str[x] == '-') { ++x; negative = -1; }

			// check for required sign
			if constexpr (!xns::is_signed<I>) {
				if (negative < 0) { value = 0;
					return false;
				}
			}

			const constexpr integer max = xns::limits::max<integer>();

			// loop through digits
			while (x < str.size() && xns::basic_string<char_t>::is_digit(str[x])) {


				integer add = (str[x] - '0');

				// check for overflow
				integer test = (max - add) / 10;

				if (value > test) {
					value = negative > 0 ? max : xns::limits::min<integer>();
					return false;
				}

				// multiply by 10 and add digit
				value = (value * 10) + add;

				++x;
			}

			// skip trailing whitespace
			while (x < str.size() && xns::basic_string<char_t>::is_whitespace(str[x])) { ++x; }

			if (x < str.size()) {
				value = 0;
				return false;
			}

			if constexpr (xns::is_signed<I>) {
				value *= negative;
			}

			return true;
		}






	};




};

#endif
