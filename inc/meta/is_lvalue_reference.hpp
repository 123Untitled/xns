#ifndef IS_LVALUE_REFERENCE_HEADER
#define IS_LVALUE_REFERENCE_HEADER

#include "integral_constant.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- I S  L V A L U E  R E F E R E N C E ---------------------------------

	/* is lvalue reference */
	template <class T>
	struct Is_lvalue_s : Xf::false_t {};

	/* is lvalue reference for lvalue reference */
	template <class T>
	struct Is_lvalue_s<T&> : Xf::true_t {};

	/* is lvalue reference value */
	template <class T>
	static constexpr bool is_lvalue_v = Is_lvalue_s<T>::value;

	/* is lvalue reference concept */
	template <class T>
	concept LeftValue = is_lvalue_v<T>;

}

#endif
