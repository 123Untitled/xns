#ifndef SAFE_ENUM_HEADER
#define SAFE_ENUM_HEADER

#include "types.hpp"
#include "type_traits.hpp"

// -- O W N  N A M E S P A C E ------------------------------------------------

namespace xns {

	/* enum definition concept */
	template <class E>
	concept enum_def = requires {
		typename E::type;
		typename E::enum_type;
	};

	/* enum max concept */
	template <class E>
	concept enum_max = requires {
		E::enum_type::MAX;
	};


	// -- S A F E  E N U M  C L A S S -----------------------------------------

	template <class E>
	class safe_enum final : public E {


		// -- R E Q U I R E M E N T S -----------------------------------------

		/* E must be an enum definition */
		static_assert(enum_def<E>, "E MUST BE AN ENUM DEFINITION");

		/* E must have a 'MAX' field */
		static_assert(enum_max<E>, "E MUST HAVE A MAXIMUM VALUE");


		public:

			// -- P U B L I C  T Y P E S --------------------------------------

			/* self type */
			using self = safe_enum<E>;

			/* definition type */
			using definition = E;

			/* integral type */
			using type = typename E::type;

			/* enum type */
			using enum_type = typename E::enum_type;


			// -- C O N S T A N T S -------------------------------------------

			/* maximum value */
			static constexpr type max = E::enum_type::MAX;


			// -- C O N S T R U C T O R S -------------------------------------

			/* default constructor */
			constexpr safe_enum(void) noexcept
			: _value{0} { }

			/* enum constructor */
			constexpr safe_enum(const enum_type value) noexcept
			: _value{value} { }


			// -- A C C E S S O R S -------------------------------------------

			/* get number of elements */
			static consteval type size(void) {
				// return maximum value
				return max;
			}

			/* get value */
			constexpr enum_type value(void) const {
				// return underlying enum value
				return _value;
			}

			/* get integral value */
			constexpr type integral(void) const {
				// return integral value
				return static_cast<type>(_value);
			}


			// -- M U T A T O R S ---------------------------------------------

			// INFO: used for 'switch' statements
			/* implicit conversion to enum type */
			constexpr operator enum_type(void) const {
				// return enum value
				return _value;
			}


		private:

			// -- M E M B E R S -----------------------------------------------

			enum_type _value;


		public:

			// -- F R I E N D S -----------------------------------------------

			///* equality operator */
			//friend constexpr bool operator==(const self& lhs, const self& rhs) noexcept {
			//	// return value equality
			//	return lhs._value == rhs._value;
			//}

			///* inequality operator */
			//friend constexpr bool operator!=(const self& lhs, const self& rhs) noexcept {
			//	// return value inequality
			//	return lhs._value != rhs._value;
			//}

			///* less than operator */
			//friend constexpr bool operator<(const self& lhs, const self& rhs) noexcept {
			//	// return value less than
			//	return lhs._value < rhs._value;
			//}

			///* greater than operator */
			//friend constexpr bool operator>(const self& lhs, const self& rhs) noexcept {
			//	// return value greater than
			//	return lhs._value > rhs._value;
			//}

			///* less than or equal operator */
			//friend constexpr bool operator<=(const self& lhs, const self& rhs) noexcept {
			//	// return value less than or equal
			//	return lhs._value <= rhs._value;
			//}

			///* greater than or equal operator */
			//friend constexpr bool operator>=(const self& lhs, const self& rhs) noexcept {
			//	// return value greater than or equal
			//	return lhs._value >= rhs._value;
			//}

	};


	// -- I S  S A F E  E N U M -----------------------------------------------

	template <class T>
	concept is_safe_enum = xns::is_same<T, xns::safe_enum<typename T::definition>>;



}


#endif