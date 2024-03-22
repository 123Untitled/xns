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

#ifndef XNS_SAFE_ENUM_HEADER
#define XNS_SAFE_ENUM_HEADER

// local headers
#include "type_traits/types.hpp"
#include "type_traits/relationships_and_property_queries/is_same.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	/* enum definition concept */
	template <typename E>
	concept enum_def = requires {
		typename E::type;
		typename E::enum_type;
	};

	/* enum max concept */
	template <typename E>
	concept enum_max = requires {
		E::enum_type::MAX;
	};


	// -- S A F E  E N U M  C L A S S -----------------------------------------

	template <typename E>
	class safe_enum final : public E {


		// -- R E Q U I R E M E N T S -----------------------------------------

		/* E must be an enum definition */
		static_assert(enum_def<E>, "): SAFE_ENUM: MUST BE AN ENUM DEFINITION :(");

		/* E must have a 'MAX' field */
		static_assert(enum_max<E>, "): SAFE_ENUM: MUST HAVE A MAXIMUM VALUE ('MAX') :(");

		/* E must have a positive 'MAX' value */
		static_assert(E::MAX >= 0, "): SAFE_ENUM: MAXIMUM VALUE ('MAX') MUST BE POSITIVE :(");



		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = safe_enum<E>;

			/* definition type */
			using definition = E;

			/* integral type */
			using type = typename E::type;

			/* enum type */
			using enum_type = typename E::enum_type;

			/* size type */
			using size_type = xns::size_t;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline constexpr safe_enum(void) noexcept
			: _value{0} {}

			/* enum constructor */
			inline constexpr safe_enum(const enum_type value) noexcept
			: _value{value} {}


			// -- public accessors --------------------------------------------

			/* get number of elements */
			inline static constexpr auto size(void) -> size_type {
				// return maximum value
				return definition::enum_type::MAX;
			}

			/* get value */
			inline constexpr auto value(void) const -> enum_type {
				// return enum value
				return _value;
			}

			/* get underlying integral value */
			constexpr auto integral(void) const -> type {
				// return integral value
				return static_cast<type>(_value);
			}


			// -- public conversion operators ---------------------------------

			// INFO: used for 'switch' statements
			/* implicit conversion to enum type */
			constexpr operator enum_type(void) const {
				// return enum value
				return _value;
			}


		private:

			// -- private members ---------------------------------------------

			/* enum value */
			enum_type _value;


	};


	// -- I S  S A F E  E N U M -----------------------------------------------

	template <typename T>
	concept is_safe_enum = xns::is_same<T, xns::safe_enum<typename T::definition>>;



} // namespace xns

#endif // XNS_SAFE_ENUM_HEADER
