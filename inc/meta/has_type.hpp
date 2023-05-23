#ifndef HAS_TYPE_HEADER
#define HAS_TYPE_HEADER

#include "integral_constant.hpp"
#include "is_same.hpp"

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- D E T A I L ---------------------------------------------------------

	namespace impl {

		template <class T, class... A>
		struct has_type : public xns::bool_constant<(xns::is_same<T, A> || ...)> {};

	}


	// -- H A S  T Y P E ------------------------------------------------------

	/* has type concept */
	template <class T, class... A>
	concept has_type = impl::has_type<T, A...>::value;

}


#endif
