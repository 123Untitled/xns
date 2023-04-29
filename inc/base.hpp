#ifndef BASE_HEADER
#define BASE_HEADER

#include "types.hpp"
#include "integral_constant.hpp"

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- B A S E -------------------------------------------------------------

	/* hexadecimal base */
	struct Hex {
		static constexpr UInt base = 16;
	};

	/* decimal base */
	struct Dec {
		static constexpr UInt base = 10;
	};

	/* octal base */
	struct Oct {
		static constexpr UInt base = 8;
	};

	/* binary base */
	struct Bin {
		static constexpr UInt base = 2;
	};


	// -- I S  B A S E --------------------------------------------------------

	/* is base false */
	template <class T>
	struct is_base      : public Xf::false_t {};

	/* is base true */
	template <>
	struct is_base<Hex> : public Xf::true_t {};

	/* is base true */
	template <>
	struct is_base<Dec> : public Xf::true_t {};

	/* is base true */
	template <>
	struct is_base<Oct> : public Xf::true_t {};

	/* is base true */
	template <>
	struct is_base<Bin> : public Xf::true_t {};


	/* is base value */
	template <class T>
	constexpr bool is_base_v = is_base<T>::value;

	/* is base concept */
	template <class T>
	concept is_base_c = Xf::is_base_v<T>;



}



#endif
