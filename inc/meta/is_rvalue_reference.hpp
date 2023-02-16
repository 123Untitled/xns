#ifndef IS_RVALUE_REFERENCE_HEADER
#define IS_RVALUE_REFERENCE_HEADER

#include "integral_constant.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- I S  R V A L U E  R E F E R E N C E ------------------------------------

	/* is rvalue reference */
	template <class T>
	struct is_rvalue_reference : false_t {};

	/* is rvalue reference for rvalue reference */
	template <class T>
	struct is_rvalue_reference<T&&> : true_t {};

	/* is rvalue reference type */
	template <class T>
	using is_rvalue_reference_t = typename is_rvalue_reference<T>::type;

	/* is rvalue reference value */
	template <class T>
	static constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;

	/* is rvalue reference concept */
	template <class T>
	concept is_rvalue_reference_c = is_rvalue_reference_v<T>;

}

#endif
