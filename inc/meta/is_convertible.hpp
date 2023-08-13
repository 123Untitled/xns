#ifndef IS_CONVERTIBLE_HEADER
#define IS_CONVERTIBLE_HEADER

// local headers
#include "declval.hpp"
#include "is_same.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- I S  C O N V E R T I B L E ------------------------------------------

	/* is convertible concept */
	template <typename From, typename To>
	concept is_convertible = requires {
		xns::is_same<To, decltype(static_cast<To>(xns::declval<From>()))>;
	};

}

#endif // IS_CONVERTIBLE_HEADER
