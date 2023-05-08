#ifndef UTILITY_HEADER
#define UTILITY_HEADER

#include "remove.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- M O V E -------------------------------------------------------------

	/* move helper */
	template <typename T>
	using ToRvalue = Xf::remove_reference_t<T>&&;

	/* move */
	template <typename T>
	inline constexpr ToRvalue<T> move(T&& obj) noexcept {
		// remove reference from T and return as rvalue reference
		return static_cast<ToRvalue<T>>(obj);
	}

}



#endif
