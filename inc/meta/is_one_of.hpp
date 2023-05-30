#ifndef HAS_TYPE_HEADER
#define HAS_TYPE_HEADER

#include "integral_constant.hpp"
#include "is_same.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- D E T A I L ---------------------------------------------------------

	namespace impl {

		template <class T, class... A>
		struct is_one_of : public xns::bool_constant<(xns::is_same<T, A> || ...)> {};

	}


	// -- I S  O N E  O F -----------------------------------------------------

	/* has type concept */
	template <class T, class... A>
	concept is_one_of = impl::is_one_of<T, A...>::value;

}


#endif
