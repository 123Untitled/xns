#ifndef IS_SAME_HEADER
#define IS_SAME_HEADER

#include "integral_constant.hpp"
#include "remove.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- I S  S A M E ---------------------------------------------------------

	/* is same false */
	template <class T, class U>
	struct is_same : Xf::false_t {};

	/* is same true */
	template <class T>
	struct is_same<T, T> : Xf::true_t {};


	template <class T, class U>
	static constexpr bool is_same_v = is_same<T, U>::value;

	/* is same concept */
	template <class T, class U>
	concept is_same_c = is_same<T, U>::value;

	/* is different */
	template <class T, class U>
	concept is_different_c = !is_same<T, U>::value;



	// -- I S  A L L  S A M E -------------------------------------------------

	/* is all same */
	template <typename T, typename...A>
	using is_all_same = Xf::bool_constant<(... && is_same_v<T, A>)>;

	/* is all same value */
	template <typename T, typename...A>
	static constexpr bool is_all_same_v = is_all_same<T, A...>::value;

	/* is all same concept */
	template <typename T, typename...A>
	concept is_all_same_c = is_all_same_v<T, A...>;

	/* is all different */
	template <typename T, typename...A>
	concept is_not_all_same = !is_all_same_v<T, A...>;





}

#endif
