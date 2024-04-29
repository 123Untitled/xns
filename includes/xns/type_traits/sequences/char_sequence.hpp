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

#ifndef XNS_CHAR_SEQUENCE_HEADER
#define XNS_CHAR_SEQUENCE_HEADER

#include "xns/type_traits/type_categories/is_char.hpp"
#include "xns/type_traits/types.hpp"
#include "xns/type_traits/relationships_and_property_queries/is_same.hpp"
#include "xns/type_traits/type_transformations/type_identity.hpp"
#include "xns/type_traits/other/string_literal.hpp"

#include <iostream>

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- C H A R A C T E R  S E Q U E N C E ----------------------------------

	template <typename __type, __type... __chars>
	class character_sequence {


		// -- assertions ------------------------------------------------------

		/* check if __type is a character type */
		static_assert(xns::is_char<__type>, "character_sequence: must be a character type");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::character_sequence<__type, __chars...>;

			/* character type */
			using char_type = __type;

			/* size type */
			using size_type = xns::size_t;



			// -- public accessors --------------------------------------------

			/* size accessor */
			static inline consteval auto size(void) noexcept -> size_type {
				return sizeof...(__chars);
			}

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

	/* implementation */
	namespace __impl {


		/* make character sequence */
		template <xns::basic_string_literal __literal,
				  xns::size_t               __begin,
				  xns::size_t               __end>
		class make_character_sequence final {


			// -- assertions ------------------------------------------------------

			/* check if begin is less than end */
			static_assert(__begin < __end,
					"make_character_sequence: begin must be less than end");

			/* check if begin is less than literal size */
			static_assert(__begin <= __literal.size(),
					"make_character_sequence: begin must be less than literal size");

			/* check if end is less than literal size */
			static_assert(__end <= __literal.size(),
					"make_character_sequence: end must be less than literal size");


			public:

				// -- public types ------------------------------------------------

				/* self type */
				using self = xns::__impl::make_character_sequence<__literal,
																  __begin,
																  __end>;

				/* character type */
				using char_type = typename decltype(__literal)::char_t;

				/* size type */
				using size_type = typename decltype(__literal)::size_type;


				// -- private implementation --------------------------------------

				/* forward declaration */
				template <size_type, char_type...>
				struct implementation;

				/* specialization for I == E, end of recursion */
				template <size_type __idx, char_type... __sequence> requires (__idx == __end)
				struct implementation<__idx, __sequence...> final {
					using __type = xns::character_sequence<char_type, __sequence...>;
				};

				/* specialization for I < E, continue recursion */
				template <size_type __idx, char_type... __sequence> requires (__idx < __end)
				struct implementation<__idx, __sequence...> final {
					using __type = typename implementation<__idx + 1, __sequence..., __literal._data[__idx]>::__type;
				};


			public:

				// -- public types ------------------------------------------------

				/* character sequence type */
				using type = typename implementation<__begin>::__type;

		};

	}


	// -- make sequence aliases -----------------------------------------------


	/* make character sequence */
	//template <xns::is_char T, xns::basic_string_literal lit>
	//using make_character_sequence = typename impl::make_character_sequence<T, 0, lit.size() - 1, lit>::type;

	template <xns::basic_string_literal __literal> // here i removed the size() - 1, because it was causing a bug
	using make_character_sequence = typename xns::__impl::make_character_sequence<__literal, 0, __literal.size()>::type;

	template <xns::basic_string_literal __literal, xns::size_t __begin, xns::size_t __end>
	using make_character_subsequence = typename xns::__impl::make_character_sequence<__literal, __begin, __end>::type;


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
