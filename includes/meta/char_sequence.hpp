#ifndef CHAR_SEQUENCE_HEADER
#define CHAR_SEQUENCE_HEADER

#include "is_char.hpp"
#include "types.hpp"
#include "is_same.hpp"
#include "identity.hpp"
#include "string_literal.hpp"

#include <iostream>

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- C H A R A C T E R  S E Q U E N C E ----------------------------------

	template <class T, T... C>
	class character_seq {


		// -- assertions ------------------------------------------------------

		/* check if T is a character type */
		static_assert(xns::is_char<T>, "T MUST BE A CHARACTER TYPE");


		public:

			// -- public types ------------------------------------------------

			/* character type */
			using char_t = T;

			/* self type */
			using self = character_seq<char_t, C...>;


			// -- public accessors --------------------------------------------

			/* size accessor */
			static inline consteval xns::size_t size(void) noexcept {
				return sizeof...(C);
			}

			/* data accessor */
			static inline consteval const char_t* data(void) noexcept {
				return _data;
			}

			/* print accessor */
			static void print(void) noexcept {
				char_t data[] = { C..., '\0' };
				std::cout << data << std::endl;
			}


		private:

			// -- private constants // INFO: to be deprecated -----------------

			/* character sequence */
			static constexpr char_t _data[sizeof...(C) + 1] = { C..., '\0' };


	};


	// -- sequence aliases ----------------------------------------------------

	/* character_seq of char */
	template <char... C>
	using char_seq   = character_seq<char, C...>;

	/* character_seq of char8_t */
	template <char8_t... C>
	using char8_seq  = character_seq<char8_t, C...>;

	/* character_seq of char16_t */
	template <char16_t... C>
	using char16_seq = character_seq<char16_t, C...>;

	/* character_seq of char32_t */
	template <char32_t... C>
	using char32_seq = character_seq<char32_t, C...>;

	/* character_seq of wchar_t */
	template <wchar_t... C>
	using wchar_seq  = character_seq<wchar_t, C...>;



	// -- M A K E  C H A R A C T E R  S E Q U E N C E -------------------------

	// -- detail --------------------------------------------------------------

	namespace impl {


		template <xns::is_char T, xns::size_t B, xns::size_t E, xns::basic_string_literal lit>
		class make_character_seq {


			// -- assertions ------------------------------------------------------

			/* check if 'begin' is less than 'end' */
			static_assert(B < E,          "START MUST BE LESS THAN END");

			/* check if 'begin' is less than literal size */
			static_assert(B < lit.size(), "BEGIN MUST BE LESS THAN LITERAL SIZE");

			/* check if 'end' is less than literal size */
			static_assert(E < lit.size(), "END MUST BE LESS THAN LITERAL SIZE");

			/* check character type match with literal */
			static_assert(xns::is_same<T, typename decltype(lit)::char_t>, "CHARACTER TYPE MISMATCH");


			public:

				// -- public types ------------------------------------------------

				/* character type */
				using char_t = T;

				/* size type */
				using size_t = xns::size_t;


			private:
			public:

				// -- private implementation --------------------------------------

				/* forward declaration */
				template <char_t...>
				struct implementation;

				/* specialization for I == E, end of recursion */
				template <size_t I, char_t... SEQ> requires (I == E)
				struct implementation<I, SEQ...> final {
					using type = xns::character_seq<char_t, SEQ...>;
				};

				/* specialization for I < E, continue recursion */
				template <size_t I, char_t... SEQ> requires (I < E)
				struct implementation<I, SEQ...> final {
					using type = typename implementation<I + 1, SEQ..., lit._data[I]>::type;
				};


			public:

				// -- public types ------------------------------------------------

				/* self type */
				using self = make_character_seq<char_t, B, E, lit>;

				/* character sequence type */
				using type = typename implementation<B>::type;

		};

	}


	// -- make sequence aliases -----------------------------------------------


	/* make character sequence */
	template <xns::is_char T, xns::basic_string_literal lit>
	using make_character_seq = typename impl::make_character_seq<T, 0, lit.size() - 1, lit>::type;



	template <xns::basic_string_literal lit>
	using make_char_seq2   = typename impl::make_character_seq<char, 0, lit.size()-1, lit>::type;

	/* make character sequence of char */
	template <xns::size_t B, xns::size_t E, xns::basic_string_literal lit>
	using make_char_seq   = typename impl::make_character_seq<char, B, E, lit>::type;

	/* make character sequence of char8_t */
	template <xns::size_t B, xns::size_t E, xns::basic_string_literal lit>
	using make_char8_seq  = typename impl::make_character_seq<char8_t, B, E, lit>::type;

	/* make character sequence of char16_t */
	template <xns::size_t B, xns::size_t E, xns::basic_string_literal lit>
	using make_char16_seq = typename impl::make_character_seq<char16_t, B, E, lit>::type;

	/* make character sequence of char32_t */
	template <xns::size_t B, xns::size_t E, xns::basic_string_literal lit>
	using make_char32_seq = typename impl::make_character_seq<char32_t, B, E, lit>::type;

	/* make character sequence of wchar_t */
	template <xns::size_t B, xns::size_t E, xns::basic_string_literal lit>
	using make_wchar_seq  = typename impl::make_character_seq<wchar_t, B, E, lit>::type;


}

#endif // CHAR_SEQUENCE_HEADER
