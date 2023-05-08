#ifndef IS_SAME_HEADER
#define IS_SAME_HEADER

#include "identity.hpp"
#include "integral_constant.hpp"
#include "remove.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- I S  S A M E ---------------------------------------------------------

	/* is same false */
	template <class T, class U>
	struct IsSame_s : Xf::false_t {};

	/* is same true */
	template <class T>
	struct IsSame_s<T, T> : Xf::true_t {};


	template <class T, class U>
	static constexpr bool is_same = IsSame_s<T, U>::value;

	template <class T, class... U>
	static constexpr bool is_all_same = (is_same<T, U> && ...);

	/* is same concept */
	template <class T, class U>
	concept IsSame = is_same<T, U>;

	/* is same concept remove specifier */
	//template <class T, class U>
	//concept IsSameRmCvr = is_same<remove_cvr_t<T>, remove_cvr_t<U>>;

	/* is same concept variadic */
	template <class T, class... U>
	concept IsAllSame = is_all_same<T, U...>;

	/* is not same */
	template <class T, class U>
	concept IsNotSame = !is_same<T, U>;

	/* is not same variadic */
	template <class T, class... U>
	concept IsNotAllSame = !is_all_same<T, U...>;



	// -- I S  A L L  S A M E -------------------------------------------------

	/* is all same */
	//template <typename T, typename...A>
	//using is_all_same = Xf::bool_constant<(... && is_same_v<T, A>)>;


	/* is all same value */
	//template <typename T, typename...A>
	//static constexpr bool is_all_same_v = is_all_same<T, A...>::value;

	/* is all same concept */
	//template <typename T, typename...A>
	//concept is_all_same_c = is_all_same_v<T, A...>;

	///* is all different */
	//template <typename T, typename...A>
	//concept is_not_all_same = !is_all_same_v<T, A...>;










}

#endif
