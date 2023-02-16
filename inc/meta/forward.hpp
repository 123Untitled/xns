#ifndef FORWARD_HEADER
#define FORWARD_HEADER

#include "enable_if.hpp"
#include "remove_reference.hpp"
#include "is_lvalue_reference.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- I D E N T I T Y -----------------------------------------------------

	// identity
	template <typename T>
	struct identity { using type = T; };


	// -- F O R W A R D -------------------------------------------------------

	// forward lvalues as rvalues
	template <typename T>
	inline constexpr typename Xf::enable_if<!Xf::is_lvalue_reference<T>::value, T&&>::type
	forward(typename Xf::identity<T>::type& obj) {
		return static_cast<T&&>(obj);
	}

	// forward rvalues as rvalues
	template <typename T>
	inline constexpr typename Xf::enable_if<!Xf::is_lvalue_reference<T>::value, T&&>::type
	forward(typename Xf::identity<T>::type&& obj) {
		return static_cast<T&&>(obj);
	}

	// forward lvalues as lvalues.
	template <typename T>
	inline constexpr typename Xf::enable_if<Xf::is_lvalue_reference<T>::value, T>::type
	forward(typename Xf::identity<T>::type obj) {
		return obj;
	}

	// prevent forwarding rvalues as const lvalues
	template <typename T>
	inline constexpr typename Xf::enable_if<Xf::is_lvalue_reference<T>::value, T>::type
	forward(typename Xf::remove_reference<T>::type&& obj) = delete;


};

#endif




