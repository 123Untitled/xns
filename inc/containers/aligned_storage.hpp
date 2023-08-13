#ifndef ALIGNED_STORAGE_HEADER
#define ALIGNED_STORAGE_HEADER

// local headers
#include "types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A L I G N E D  S T O R A G E  S T R U C T ---------------------------

	template <xns::size_t L, decltype(L) A>
	struct aligned_storage final {


		// -- public members --------------------------------------------------

		alignas(A) xns::ubyte _data[L];


		// -- public accessors ------------------------------------------------

		/* data */
		inline constexpr auto data(void) noexcept -> xns::ubyte* {
			return _data;
		}

		/* size */
		inline consteval auto size(void) const noexcept -> decltype(L) {
			return L;
		}


		// -- public conversion -----------------------------------------------

		/* cast to type reference */
		template <class T>
		inline constexpr auto to_reference(void) noexcept -> T& {
			return *static_cast<T*>(static_cast<void*>(_data));
		}

		/* cast to const type reference */
		template <class T>
		inline constexpr auto to_reference(void) const noexcept -> const T& {
			return *static_cast<const T*>(static_cast<const void*>(_data));
		}

		/* cast to type pointer */
		template <class T>
		inline constexpr auto to_pointer(void) noexcept -> T* {
			return static_cast<T*>(static_cast<void*>(_data));
		}

		/* cast to const type pointer */
		template <class T>
		inline constexpr auto to_pointer(void) const noexcept -> const T* {
			return static_cast<const T*>(static_cast<const void*>(_data));
		}


	};

	/* get max size of parameter pack */
	template <class... A>
	consteval auto size_of_max(void) -> xns::size_t {
		xns::size_t size = 0;
		((size = (sizeof(A) > size ? sizeof(A) : size)), ...);
		return size;
	}

	/* get max alignment of parameter pack */
	template <class... A>
	consteval auto align_of_max(void) -> xns::size_t {
		xns::size_t align = 0;
		((align = (alignof(A) > align ? alignof(A) : align)), ...);
		return align;
	}

}

#endif // ALIGNED_STORAGE_HEADER

