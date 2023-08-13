#ifndef IS_DESTRUCTIBLE_HEADER
#define IS_DESTRUCTIBLE_HEADER

// local headers
#include "config.hpp"

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  D E S T R U C T I B L E ----------------------------------------

#if __has_builtin(__is_destructible)

	/* is destructible concept */
	template <class T>
	concept is_destructible = __is_destructible(T);

#else

	/* is destructible concept */
	template <class T>
	concept is_destructible = requires(T t) {
		{ t.~T() };
	};

#endif


}


#endif // IS_DESTRUCTIBLE_HEADER
