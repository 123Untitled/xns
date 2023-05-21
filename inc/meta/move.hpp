#ifndef UTILITY_HEADER
#define UTILITY_HEADER

#include "to_reference.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- M O V E -------------------------------------------------------------

	/* move */
	template <typename T>
	inline constexpr xns::to_rvalue<T> move(T&& obj) noexcept {
		// remove reference from T and return as rvalue reference
		return static_cast<xns::to_rvalue<T>>(obj);
	}

}


#endif
