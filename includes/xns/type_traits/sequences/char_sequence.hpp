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

#include "xns/type_traits/types.hpp"
#include "xns/type_traits/other/string_literal.hpp"
#include "xns/type_traits/type_categories/is_char.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- C H A R A C T E R  S E Q U E N C E ----------------------------------

	template <typename ___type, ___type... ___chars>
	class character_sequence final {


		// -- assertions ------------------------------------------------------

		/* check if __type is a character type */
		static_assert(xns::is_char<___type>, "character_sequence: must be a character type");


		private:

			// -- public types ------------------------------------------------

			/* self type */
			using ___self = xns::character_sequence<___type, ___chars...>;


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type = ___type;

			/* size type */
			using size_type = xns::size_t;


			// -- public accessors --------------------------------------------

			/* size */
			static consteval auto size(void) noexcept -> size_type {
				return sizeof...(___chars);
			}

	}; // character_sequence


	// -- sequence aliases ----------------------------------------------------

	/* character_seq of char */
	template <char...     ___chars>
	using char_sequence   = xns::character_sequence<char,     ___chars...>;

	/* character_seq of char8_t */
	template <char8_t...  ___chars>
	using char8_sequence  = xns::character_sequence<char8_t,  ___chars...>;

	/* character_seq of char16_t */
	template <char16_t... ___chars>
	using char16_sequence = xns::character_sequence<char16_t, ___chars...>;

	/* character_seq of char32_t */
	template <char32_t... ___chars>
	using char32_sequence = xns::character_sequence<char32_t, ___chars...>;

	/* character_seq of wchar_t */
	template <wchar_t...  ___chars>
	using wchar_sequence  = xns::character_sequence<wchar_t,  ___chars...>;



	// -- M A K E  C H A R A C T E R  S E Q U E N C E -------------------------

	namespace ___impl {


		/* make character sequence */
		template <xns::basic_string_literal ___literal,
				  xns::size_t               ___begin,
				  xns::size_t               ___end>
		class ___make_character_sequence final {


			// -- assertions --------------------------------------------------

			/* check if begin is less than end */
			static_assert(___begin < ___end,
					"make_character_sequence: begin must be less than end");

			/* check if begin is less than literal size */
			static_assert(___begin <= ___literal.size(),
					"make_character_sequence: begin must be less than literal size");

			/* check if end is less than literal size */
			static_assert(___end <= ___literal.size(),
					"make_character_sequence: end must be less than literal size");


			private:

				// -- private types -------------------------------------------

				/* self type */
				using ___self = xns::___impl::___make_character_sequence<___literal, ___begin, ___end>;


			public:

				// -- public types --------------------------------------------

				/* value type */
				using value_type = typename decltype(___literal)::value_type;

				/* size type */
				using size_type = typename decltype(___literal)::size_type;


				// -- public lifecycle ----------------------------------------

				/* non-instantiable */
				___xns_not_instantiable(___make_character_sequence);


				// -- private implementation ----------------------------------

				/* forward declaration */
				template <size_type, value_type...>
				struct ___;

				/* specialization for I == E, end of recursion */
				template <size_type ___idx, value_type... ___seq> requires (___idx == ___end)
				struct ___<___idx, ___seq...> final {
					using ___type = xns::character_sequence<value_type, ___seq...>;
					___xns_not_instantiable(___);
				};

				/* specialization for I < E, continue recursion */
				template <size_type ___idx, value_type... ___seq> requires (___idx < ___end)
				struct ___<___idx, ___seq...> final {
					using ___type = typename ___<___idx + 1U, ___seq..., ___literal._data[___idx]>::___type;
					___xns_not_instantiable(___);
				};


			public:

				// -- public types --------------------------------------------

				/* character sequence type */
				using type = typename ___self::___<___begin>::___type;

		}; // class ___make_character_sequence

	} // namespace ___impl


	// -- make sequence aliases -----------------------------------------------

	/* make character sequence */
	template <xns::basic_string_literal ___literal> // here i removed the size() - 1, because it was causing a bug
	using make_character_sequence = typename xns::___impl::___make_character_sequence<___literal, 0U, ___literal.size()>::type;

	/* make character subsequence */
	template <xns::basic_string_literal ___literal, xns::size_t ___begin, xns::size_t ___end>
	using make_character_subsequence = typename xns::___impl::___make_character_sequence<___literal, ___begin, ___end>::type;

} // namespace xns

#endif // XNS_CHAR_SEQUENCE_HEADER
