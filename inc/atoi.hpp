#ifndef ATOI_HEADER
#define ATOI_HEADER

#include "string.hpp"
#include "types.hpp"
#include "type_traits.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	template <xns::is_string S, is_integral I>
	bool string_to_integer(const S& str, I& value) {

		/* integer type */
		using integer       = xns::remove_cvr<I>;
		/* string type */
		using string_type   = xns::remove_cvr<S>;
		/* size type */
		using size_type     = string_type::size_type;
		/* character type */
		using char_t        = string_type::char_t;
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
			&& xns::string<char_t>::is_whitespace(str[x])) {
			++x;
		}

		// check for sign
		if      (str[x] == '+') { ++x;                }
		else if (str[x] == '-') { ++x; negative = -1; }

		// check for required sign
		if constexpr (!Xf::is_signed_integral_c<I>) {
			if (negative < 0) { value = 0;
				return false;
			}
		}

		const constexpr integer max = xns::max<integer>();

		// loop through digits
		while (x < str.size() && xns::string<char_t>::is_digit(str[x])) {


			integer add = (str[x] - '0');

			// check for overflow
			integer test = (max - add) / 10;

			if (value > test) {
				value = negative > 0 ? max : xns::min<integer>();
				return false;
			}

			// multiply by 10 and add digit
			value = (value * 10) + add;

			++x;
		}

		// skip trailing whitespace
		while (x < str.size() && xns::string<char_t>::is_whitespace(str[x])) { ++x; }

		if (x < str.size()) {
			value = 0;
			return false;
		}

		if constexpr (Xf::is_signed_integral_c<I>) {
			value *= negative;
		}

		return true;
	}





}

#endif
