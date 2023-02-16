#ifndef IS_LVALUE_REFERENCE_HEADER
#define IS_LVALUE_REFERENCE_HEADER

#include "integral_constant.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- I S  L V A L U E  R E F E R E N C E ------------------------------------

	/* is lvalue reference */
	template <class T>
	struct is_lvalue_reference : false_t {};

	/* is lvalue reference for lvalue reference */
	template <class T>
	struct is_lvalue_reference<T&> : true_t {};

	/* is lvalue reference type */
	template <class T>
	using is_lvalue_reference_t = typename is_lvalue_reference<T>::type;

	/* is lvalue reference value */
	template <class T>
	static constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

	/* is lvalue reference concept */
	template <class T>
	concept is_lvalue_reference_c = is_lvalue_reference_v<T>;

}

#endif
