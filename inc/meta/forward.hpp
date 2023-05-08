#ifndef FORWARD_HEADER
#define FORWARD_HEADER

#include "enable_if.hpp"
#include "remove.hpp"
#include "is_lvalue_reference.hpp"
#include "identity.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	/* forward lvalue helper */
	template <typename T>
	using ToLvalue = Xf::remove_reference_t<T>&;

	/* forward rvalue helper */
	template <typename T>
	using ToRvalue = Xf::remove_reference_t<T>&&;


	// -- F O R W A R D -------------------------------------------------------

	// forward lvalues as lvalues
	template <class T>
	inline constexpr T&& forward(ToLvalue<T> obj) noexcept {
		// cast to T&(&&) = T&
		return static_cast<T&&>(obj);
	}

	// forward rvalues as rvalues
	template <class T>
	inline constexpr T&& forward(ToRvalue<T> obj) noexcept {
		// cast to T&&(&&) = T&&
		return static_cast<T&&>(obj);
	}


};

#endif


















