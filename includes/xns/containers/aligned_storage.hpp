/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_ALIGNED_STORAGE_HEADER
#define XNS_ALIGNED_STORAGE_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A L I G N E D  S T O R A G E ----------------------------------------

	template <decltype(sizeof(0)) S, decltype(S) A>
	struct aligned_storage final {


		// -- public types ----------------------------------------------------

		/* self type */
		using self = xns::aligned_storage<S, A>;

		/* size type */
		using size_type = decltype(S);


		// -- public members --------------------------------------------------

		alignas(A) unsigned char _data[S];


		// -- public accessors ------------------------------------------------

		/* size */
		inline consteval auto size(void) const noexcept -> size_type {
			return S;
		}

	}; // struct aligned_storage


	// -- non-member functions ------------------------------------------------

	/* cast to pointer */
	template <typename T, decltype(sizeof(0)) S, decltype(S) A>
	inline constexpr auto ptr(xns::aligned_storage<S, A>& storage) noexcept -> T* {
		// assert that the type is not too big
		static_assert(sizeof(T) <= S, "ptr: aligned_storage is too small");
		return static_cast<T*>(static_cast<void*>(storage._data));
	}

	/* cast to const pointer */
	template <typename T, decltype(sizeof(0)) S, decltype(S) A>
	inline constexpr auto ptr(const xns::aligned_storage<S, A>& storage) noexcept -> const T* {
		// assert that the type is not too big
		static_assert(sizeof(T) <= S, "ptr: aligned_storage is too small");
		return static_cast<const T*>(static_cast<const void*>(storage._data));
	}

	/* cast to reference */
	template <typename T, decltype(sizeof(0)) S, decltype(S) A>
	inline constexpr auto ref(xns::aligned_storage<S, A>& storage) noexcept -> T& {
		// assert that the type is not too big
		static_assert(sizeof(T) <= S, "ptr: aligned_storage is too small");
		return *(static_cast<T*>(static_cast<void*>(storage._data)));
	}

	/* cast to const reference */
	template <typename T, decltype(sizeof(0)) S, decltype(S) A>
	inline constexpr auto ref(const xns::aligned_storage<S, A>& storage) noexcept -> const T& {
		// assert that the type is not too big
		static_assert(sizeof(T) <= S, "ptr: aligned_storage is too small");
		return *(static_cast<const T*>(static_cast<const void*>(storage._data)));
	}


}

#endif // ALIGNED_STORAGE_HEADER
