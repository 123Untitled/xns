#ifndef TO_STRING_HEADER
#define TO_STRING_HEADER

#include "string.hpp"
#include "types.hpp"
#include "is_signed.hpp"
#include "numeric_limits.hpp"
#include "macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {



	/* to basic string (signed integer) */
	template <typename C, typename T>
	auto to_basic_string(T vlue) -> xns::basic_string<C>
		// requirements
		requires(xns::is_signed_integral<T>) {

		T value = vlue;
		xns::basic_string<C> str;

		str.reserve(xns::limits::digits<T>() + 1); // INFO: +1 for negative sign

		constexpr T type_min = xns::limits::min<T>();

		T base = 10;

		bool negative = false;

		xns::string::size_type x = 0;

		// check negative
		if (value < 0) {
			// set negative flag
			negative = true;

			if (value == type_min) {
				// INFO: this is a special case
			}
			else {
				// inverse number
				value = -value;
			}
		}

		do {
			T rem = value % base;
			//_str[x] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
			str._str[x] = (value % 10) + '0';
			++x;
		} while ((value /= base));

		if (negative) { str._str[x++] = '-'; }

		str.null_terminator(x);
		// reverse all characters
		str.reverse();

		return str;
	}


	/* to basic string (unsigned integer) */
	template <typename C, typename T>
	auto to_basic_string(T number) -> xns::basic_string<C>
		// requirements
		requires(xns::is_unsigned_integral<T>) {

		using size_type = typename xns::basic_string<C>::size_type;

		xns::basic_string<C> str;
		constexpr size_type size = xns::limits::digits<T>();

		str._str = str.allocate(size);
		str._capacity = size;

		// declare iterator
		size_type x = 0;

		// loop through number
		do {
			str._str[x] = (number % 10) + '0';
			number /= 10;
			++x;
		} while (number);

		str._str[x] = static_cast<C>(0);
		str._size = x;

		// reverse all characters
		str.reverse();

		return str;
	}




		template <xns::is_string S, is_integral I>
		static bool to_integer(const S& str, I& value) {

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




	/* to c-string ascii */
	template <typename T>
	inline auto to_string(const T& value) -> xns::string {
		return to_basic_string<typename xns::string::char_t, T>(value);
	}

	/* to wide string */
	template <typename T>
	inline auto to_wstring(const T& value) -> xns::wstring {
		return to_basic_string<typename xns::wstring::char_t, T>(value);
	}

	/* to utf-8 string */
	template <typename T>
	inline auto to_u8string(const T& value) -> xns::u8string {
		return to_basic_string<typename xns::u8string::char_t, T>(value);
	}

	/* to utf-16 string */
	template <typename T>
	inline auto to_u16string(const T& value) -> xns::u16string {
		return to_basic_string<typename xns::u16string::char_t, T>(value);
	}

	/* to utf-32 string */
	template <typename T>
	inline auto to_u32string(const T& value) -> xns::u32string {
		return to_basic_string<typename xns::u32string::char_t, T>(value);
	}






}

#endif

			// /* unsigned integer to string */
			// template <xns::is_unsigned N>
			// void to_string(N number) {
			// 	// temporary string
			// 	clear();
			//
			// 	constexpr N size = xns::limits::digits<N>();
			//
			// 	// WARNING: need to verify class
			// 	// error doesn't checked with this method
			// 	reserve(size);
			//
			// 	// convert number to string
			// 	size_type x = 0;
			// 	// loop through number
			// 	do {
			// 		_str[x] = (number % 10) + '0';
			// 		number /= 10;
			// 		++x;
			// 	} while (number);
			//
			// 	_size_and_terminator(x);
			// 	// reverse all characters
			// 	reverse();
			// }
			//
			//
			// /* signed integer to string */
			// template <xns::is_signed N>
			// void to_string(N number) {
			// 	// temporary string
			// 	clear();
			//
			// 	constexpr size_type size = xns::limits::digits<N>() + 1; // INFO: +1 for negative sign
			// 	constexpr N type_min = xns::limits::min<N>();
			// 	N base = 10;
			//
			// 	// WARNING: need to verify class
			// 	// error doesn't checked with this method
			// 	reserve(size);
			// 	bool negative = false;
			//
			// 	size_type x = 0;
			// 	// check negative
			// 	if (number < 0) {
			// 		// set negative flag
			// 		negative = true;
			//
			// 		if (number == type_min) {
			// 			// INFO: this is a special case
			// 		}
			// 		else {
			// 			// inverse number
			// 			number = -number;
			// 		}
			// 	}
			// 	do {
			// 		N rem = number % base;
			// 		//_str[x] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
			// 		_str[x] = (number % 10) + '0';
			// 		++x;
			// 	} while ((number /= base));
			//
			// 	if (negative) { _str[x++] = '-'; }
			//
			// 	_size_and_terminator(x);
			// 	// reverse all characters
			// 	reverse();
			// }
			//
