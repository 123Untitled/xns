#ifndef XNS_IS_ONE_OF_HPP
#define XNS_IS_ONE_OF_HPP

#include "is_same.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- I S  O N E  O F -----------------------------------------------------

	/* is one of concept */
	template <typename T, typename... A>
	concept is_one_of = (xns::is_same<T, A> || ...);

}

#endif // XNS_IS_ONE_OF_HPP
