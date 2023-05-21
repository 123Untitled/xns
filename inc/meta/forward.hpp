#ifndef FORWARD_HEADER
#define FORWARD_HEADER

#include "to_reference.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- F O R W A R D -------------------------------------------------------

	// forward lvalues as lvalues
	template <class T>
	inline constexpr T&& forward(xns::to_lvalue<T> obj) noexcept {
		// cast to T&(&&) = T&
		return static_cast<T&&>(obj);
	}

	// forward rvalues as rvalues
	template <class T>
	inline constexpr T&& forward(xns::to_rvalue<T> obj) noexcept {
		// cast to T&&(&&) = T&&
		return static_cast<T&&>(obj);
	}


};

#endif


















