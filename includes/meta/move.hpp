#ifndef XNS_MOVE_HEADER
#define XNS_MOVE_HEADER

#include "to_reference.hpp"
#include "is_const.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M O V E -------------------------------------------------------------

	/* move */
	template <typename T>
	inline constexpr auto move(T&& obj) noexcept -> xns::to_rvalue<T> {
		// assert that T is not const (not following the standard)
		static_assert(not xns::is_const<T>, "): MOVE: cannot move const object :(");
		// remove reference from T and return as rvalue reference
		return static_cast<xns::to_rvalue<T>>(obj);
	}

}


#endif
