#ifndef IS_SAME_HEADER
#define IS_SAME_HEADER

#include "integral_constant.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- I S  S A M E ---------------------------------------------------------

	/* is same */
	template <typename T, typename U>
	struct is_same : false_t {};

	/* is same for same types */
	template <typename T>
	struct is_same<T, T> : true_t {};

	/* is same type */
	template <typename T, typename U>
	using is_same_t = typename is_same<T, U>::type;

	/* is same value */
	template <typename T, typename U>
	static constexpr bool is_same_v = is_same<T, U>::value;

	/* is same concept */
	template <typename T, typename U>
	concept is_same_c = is_same_v<T, U>;

}

#endif
