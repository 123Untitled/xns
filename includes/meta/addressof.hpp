#ifndef XNS_ADDRESSOF_HEADER
#define XNS_ADDRESSOF_HEADER

#include "is_class.hpp"
#include "is_union.hpp"
#include "is_array.hpp"
#include "is_scalar.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- A D D R E S S O F ---------------------------------------------------


	// not finished !!!

	/* addressof */
	template <typename T> requires (xns::is_class<T> == true || xns::is_union<T> == true)
	inline constexpr auto addressof(T& value) noexcept {
		// cast to char& to get address
		return reinterpret_cast<T*>(&(reinterpret_cast<char&>(value)));
	}

	/* addressof */
	template <typename T> requires (xns::is_array<T> == true)
	inline constexpr auto addressof(T& value) noexcept {
		// just return address of first element
		return &(value[0]);
	}

	/* addressof */
	template <typename T> requires (xns::is_scalar<T> == true)
	inline constexpr auto addressof(T& value) noexcept {
		// just return address
		return &value;
	}


	/* deleted const addressof */
	template <typename T>
	auto addressof(const T&&) = delete;

}

#endif
