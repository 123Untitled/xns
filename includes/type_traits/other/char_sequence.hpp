#ifndef XNS_CHAR_SEQUENCE_HEADER
#define XNS_CHAR_SEQUENCE_HEADER

#include "is_char.hpp"
#include "types.hpp"
#include "is_same.hpp"
#include "identity.hpp"
#include "string_literal.hpp"

#include <iostream>

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- C H A R A C T E R  S E Q U E N C E ----------------------------------

	template <typename T, T... C>
	class character_sequence {


		// -- assertions ------------------------------------------------------

		/* check if T is a character type */
		static_assert(xns::is_char<T>, "T MUST BE A CHARACTER TYPE");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = character_sequence<T, C...>;

			/* character type */
			using char_type = T;

			/* size type */
			using size_type = xns::size_t;



			// -- public accessors --------------------------------------------

			/* size accessor */
			static inline consteval auto size(void) noexcept -> size_type {
				return sizeof...(C);
			}

			/* data accessor */
			static inline consteval auto data(void) noexcept -> const char_type* {
				return _data;
			}

			/* print accessor */
			static auto print(void) noexcept -> void {
				char_type data[] = { C..., '\0' };
				std::cout << data << std::endl;
			}


		private:

			// -- private constants // INFO: to be deprecated -----------------

			/* character sequence */
			static constexpr char_type _data[sizeof...(C) + 1] = { C..., '\0' };

	};


	// -- sequence aliases ----------------------------------------------------

	/* character_seq of char */
	template <char...     C>
	using char_sequence   = xns::character_sequence<char,     C...>;

	/* character_seq of char8_t */
	template <char8_t...  C>
	using char8_sequence  = xns::character_sequence<char8_t,  C...>;

	/* character_seq of char16_t */
	template <char16_t... C>
	using char16_sequence = xns::character_sequence<char16_t, C...>;

	/* character_seq of char32_t */
	template <char32_t... C>
	using char32_sequence = xns::character_sequence<char32_t, C...>;

	/* character_seq of wchar_t */
	template <wchar_t...  C>
	using wchar_sequence  = xns::character_sequence<wchar_t,  C...>;



	// -- M A K E  C H A R A C T E R  S E Q U E N C E -------------------------

	// -- detail --------------------------------------------------------------

	namespace impl {


		template <xns::basic_string_literal lit, xns::size_t B, xns::size_t E>
		class make_character_sequence {


			// -- assertions ------------------------------------------------------

			/* check if 'begin' is less than 'end' */
			static_assert(B < E,          "START MUST BE LESS THAN END");

			/* check if 'begin' is less than literal size */
			static_assert(B <= lit.size(), "BEGIN MUST BE LESS THAN LITERAL SIZE");

			/* check if 'end' is less than literal size */
			static_assert(E <= lit.size(), "END MUST BE LESS THAN LITERAL SIZE");


			public:

				// -- public types ------------------------------------------------

				/* character type */
				using char_t = typename decltype(lit)::char_t;

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
					using type = xns::character_sequence<char_t, SEQ...>;
				};

				/* specialization for I < E, continue recursion */
				template <size_t I, char_t... SEQ> requires (I < E)
				struct implementation<I, SEQ...> final {
					using type = typename implementation<I + 1, SEQ..., lit._data[I]>::type;
				};


			public:

				// -- public types ------------------------------------------------

				/* self type */
				using self = make_character_sequence<lit, B, E>;

				/* character sequence type */
				using type = typename implementation<B>::type;

		};

	}


	// -- make sequence aliases -----------------------------------------------


	/* make character sequence */
	//template <xns::is_char T, xns::basic_string_literal lit>
	//using make_character_sequence = typename impl::make_character_sequence<T, 0, lit.size() - 1, lit>::type;

	template <xns::basic_string_literal lit> // here i removed the size() - 1, because it was causing a bug
	using make_character_sequence = typename impl::make_character_sequence<lit, 0, lit.size()>::type;

	template <xns::basic_string_literal lit, xns::size_t B, xns::size_t E>
	using make_character_subsequence = typename impl::make_character_sequence<lit, B, E>::type;


	/* make character sequence of char */
	//template <xns::size_t B, xns::size_t E, xns::basic_string_literal lit>
	//using make_char_sequence   = typename impl::make_character_sequence<char, B, E, lit>::type;
	//
	///* make character sequence of char8_t */
	//template <xns::size_t B, xns::size_t E, xns::basic_string_literal lit>
	//using make_char8_sequence  = typename impl::make_character_sequence<char8_t, B, E, lit>::type;
	//
	///* make character sequence of char16_t */
	//template <xns::size_t B, xns::size_t E, xns::basic_string_literal lit>
	//using make_char16_sequence = typename impl::make_character_sequence<char16_t, B, E, lit>::type;
	//
	///* make character sequence of char32_t */
	//template <xns::size_t B, xns::size_t E, xns::basic_string_literal lit>
	//using make_char32_sequence = typename impl::make_character_sequence<char32_t, B, E, lit>::type;
	//
	///* make character sequence of wchar_t */
	//template <xns::size_t B, xns::size_t E, xns::basic_string_literal lit>
	//using make_wchar_sequence  = typename impl::make_character_sequence<wchar_t, B, E, lit>::type;


}

#endif // CHAR_SEQUENCE_HEADER
