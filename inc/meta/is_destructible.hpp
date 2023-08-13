#ifndef IS_DESTRUCTIBLE_HEADER
#define IS_DESTRUCTIBLE_HEADER

// local headers
#include "config.hpp"
#include "declval.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  D E S T R U C T I B L E ----------------------------------------

	template <typename T>
	concept is_destructible = requires {
		{ xns::declval<T&>().~T() };
	};

}

#endif // IS_DESTRUCTIBLE_HEADER
