#ifndef UTILITY_HEADER
#define UTILITY_HEADER

#include "type_traits.hpp"

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- M O V E -------------------------------------------------------------

	/* move */
	template <typename T>
	inline constexpr typename Xf::remove_reference<T>::type&& move(T&& obj) noexcept {
		// remove reference from T and return as rvalue reference
		return static_cast<typename Xf::remove_reference<T>::type&&>(obj);
	}


}



#endif
