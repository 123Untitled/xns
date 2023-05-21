#ifndef BASE_HEADER
#define BASE_HEADER

#include "types.hpp"
#include "integral_constant.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- B A S E -------------------------------------------------------------

	/* hexadecimal base */
	struct Hex {
		static constexpr xns::u8 base = 16;
	};

	/* decimal base */
	struct Dec {
		static constexpr xns::u8 base = 10;
	};

	/* octal base */
	struct Oct {
		static constexpr xns::u8 base = 8;
	};

	/* binary base */
	struct Bin {
		static constexpr xns::u8 base = 2;
	};


	// -- I S  B A S E --------------------------------------------------------

	/* is base false */
	template <class T>
	struct is_base      : public xns::no {};

	/* is base true */
	template <>
	struct is_base<Hex> : public xns::yes {};

	/* is base true */
	template <>
	struct is_base<Dec> : public xns::yes {};

	/* is base true */
	template <>
	struct is_base<Oct> : public xns::yes {};

	/* is base true */
	template <>
	struct is_base<Bin> : public xns::yes {};


	/* is base value */
	template <class T>
	constexpr bool is_base_v = is_base<T>::value;

	/* is base concept */
	template <class T>
	concept is_base_c = xns::is_base_v<T>;



}



#endif
