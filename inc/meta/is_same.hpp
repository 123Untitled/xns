#ifndef IS_SAME_HEADER
#define IS_SAME_HEADER

#include "identity.hpp"
#include "integral_constant.hpp"
#include "remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  S A M E ---------------------------------------------------------

	/* is same false */
	template <class T, class U>
	struct _is_same : xns::no {};

	/* is same true */
	template <class T>
	struct _is_same<T, T> : xns::yes {};

	/* is same concept */
	template <class T, class U>
	concept is_same = _is_same<T, U>::value;

	/* is not same concept */
	template <class T, class U>
	concept is_not_same = !is_same<T, U>;


	// -- I S  A L L  S A M E -------------------------------------------------

	// INFO: does i need to remove cvr?
	// answer: no, because cvr is not part of the type

	/* is all same concept */
	template <class T, class... U>
	concept is_all_same = (is_same<T, U> && ...);

	/* is not all same concept */
	template <class T, class... U>
	concept is_not_all_same = !is_all_same<T, U...>;


	/* is same concept remove specifier */
	//template <class T, class U>
	//concept IsSameRmCvr = is_same<remove_cvr_t<T>, remove_cvr_t<U>>;


}

#endif
