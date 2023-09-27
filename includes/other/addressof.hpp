#ifndef ADDRESSOF_HEADER
#define ADDRESSOF_HEADER

#include <type_traits>

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A D D R E S S O F ---------------------------------------------------

	template <typename T> requires (std::is_object_v<T>)
	inline auto addressof(T& arg) noexcept -> T* {
		return reinterpret_cast<T*>(
			&const_cast<char&>(
				reinterpret_cast<const volatile char&>(arg)
			)
		);
	}

	template <typename T> requires (not std::is_object_v<T>)
	inline auto addressof(T& arg) noexcept -> T* {
		return &arg;
	}

	template <typename T>
	auto addressof(const T&& arg) -> const T* = delete;


}

#endif // ADDRESSOF_HEADER
