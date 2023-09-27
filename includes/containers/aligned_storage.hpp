#ifndef ALIGNED_STORAGE_HEADER
#define ALIGNED_STORAGE_HEADER

// local headers
#include "types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A L I G N E D  S T O R A G E ----------------------------------------

	template <xns::size_t L, decltype(L) A>
	struct aligned_storage final {


		// -- public types ----------------------------------------------------

		/* self type */
		using self = xns::aligned_storage<L, A>;


		// -- public members --------------------------------------------------

		alignas(A) xns::ubyte _data[L];


		// -- public accessors ------------------------------------------------

		/* size */
		inline consteval auto size(void) const noexcept -> decltype(L) {
			return L;
		}

	};


	// -- non-member functions ------------------------------------------------

	/* cast to pointer */
	template <typename T, xns::size_t L, decltype(L) A>
	inline constexpr auto ptr(xns::aligned_storage<L, A>& storage) noexcept -> T* {
		// assert that the type is not too big
		static_assert(sizeof(T) <= L,
				"): ALIGNED STORAGE: IS TOO SMALL! :(");
		return static_cast<T*>(static_cast<void*>(storage._data));
	}

	/* cast to const pointer */
	template <typename T, xns::size_t L, decltype(L) A>
	inline constexpr auto ptr(const xns::aligned_storage<L, A>& storage) noexcept -> const T* {
		// assert that the type is not too big
		static_assert(sizeof(T) <= L,
				"): ALIGNED STORAGE: IS TOO SMALL! :(");
		return static_cast<const T*>(static_cast<const void*>(storage._data));
	}

	/* cast to reference */
	template <typename T, xns::size_t L, decltype(L) A>
	inline constexpr auto ref(xns::aligned_storage<L, A>& storage) noexcept -> T& {
		// assert that the type is not too big
		static_assert(sizeof(T) <= L,
				"): ALIGNED STORAGE: IS TOO SMALL! :(");
		return *(static_cast<T*>(static_cast<void*>(storage._data)));
	}

	/* cast to const reference */
	template <typename T, xns::size_t L, decltype(L) A>
	inline constexpr auto ref(const xns::aligned_storage<L, A>& storage) noexcept -> const T& {
		// assert that the type is not too big
		static_assert(sizeof(T) <= L,
				"): ALIGNED STORAGE: IS TOO SMALL! :(");
		return *(static_cast<const T*>(static_cast<const void*>(storage._data)));
	}


}

#endif // ALIGNED_STORAGE_HEADER

