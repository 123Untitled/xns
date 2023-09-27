#ifndef PRINT_HEADER
#define PRINT_HEADER

// this header implements a printf-like function but with a few differences:
// 1. string format is a compile-time expression
// 2. it is type-safe
// 3. it is constexpr

#include "string_literal.hpp"
#include "string.hpp"
#include "types.hpp"
#include "integer_sequence.hpp"

#include <array>

namespace xns {

	// -- L I T E R A L  T E M P L A T E --------------------------------------

	template <xns::is_char T, T... C>
	class literal_template {

		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = literal_template<T, C...>;

			/* character type */
			using char_t = T;

			/* const pointer type */
			using const_pointer = const char_t*;

	};


	// -- S T R I N G  F O R M A T --------------------------------------------

	class format {


		public:


			template <xns::size_t N>
			struct store {

				int _data[N];

			};

			// -- public types ------------------------------------------------

			/* character type */
			//using char_t = T;

			/* self type */
			//using self = format<T, A...>;

			/* const pointer type */
			//using const_pointer = const char_t*;

			/* size type */
			using size_type = xns::size_t;

			template <xns::is_char T, xns::size_t N, xns::size_t I>
			consteval static size_type len(const T (&str)[N]) {
				return (str[I] == '\0') ? I : len(str, I + 1);
			}

			template<xns::is_char T, xns::size_t N, size_t... I>
			consteval void copy_array(T (&dest)[N], const T (&src)[N], xns::index_seq<I...>) {
				((dest[I] = src[I]), ...);
			}

			// -- public constructors -----------------------------------------

			template <xns::is_char T, xns::size_t N>
			static consteval void test(const xns::basic_string_literal<T, N>& str) {
			}

			template <xns::basic_string_literal lit, xns::size_t... N>
			static consteval auto split(const xns::index_seq<N...>& seq) {


				xns::array<xns::string_view, sizeof...(N)> ar;




				return ar;
			}

			/* format string constructor */
			template <xns::basic_string_literal lit, class... A>
			static consteval auto print(const A&... args) {


				// get format specifier number
				constexpr const size_type segments = specifier_number<lit>();


				/*xns::array<xns::string_view, segments> ar = {
					lit.data()
				};*/



				return segments;

				//return ar;
				// store format specifiers
				//constexpr xns::string_view t[segments];
				//auto s = xns::make_index_sequence<segments>{};


			}




		private:

			// -- private static methods --------------------------------------

			/* get format specifier number */
			template <xns::basic_string_literal lit>
			static consteval size_type specifier_number(void) {

				auto ar = lit.data();
				xns::size_t count = 0;

				xns::size_t i = 0;
				while (i < lit.size()) {

					if (ar[i] == '{' && ar[i + 1] != '{') {
						++count;
						while (ar[i] != '}') { ++i; }

						continue;
					}
					++i;
				}
				return count;
			}

			// -- private members ---------------------------------------------


	};





	/*
	template <class... A>
	constexpr void print(const char* format, A... args) {
		xns::size_t x = 0;
		while (format[x]) {

			++x;

		}
	}
	*/

}



#endif
