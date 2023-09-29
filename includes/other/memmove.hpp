#ifndef XNS_MEMMOVE_HEADER
#define XNS_MEMMOVE_HEADER

// local headers
#include "types.hpp"

#include <iostream>

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- detail --------------------------------------------------------------

	namespace impl {

		inline auto memmove(xns::ubyte* dst, const xns::ubyte* src, xns::size_t size) -> void {

			while (dst < src && size) {
				*(dst++) = *(src++);
				--size;
			}

			while (dst > src && size) {
				--size;
				*(dst + size) = *(src + size);
			}
		}

	}


	// -- M E M M O V E -------------------------------------------------------

	/* memmove */
	template <typename D, typename S>
	inline auto memmove(D* dst, const S* src, const xns::size_t size) -> void {
		// check if types have the same size
		static_assert(sizeof(D) == sizeof(S), "): MEMMOVE: TYPES HAVE DIFFERENT SIZE :(");
		// call implementation with ubyte pointers and size in bytes
		impl::memmove(static_cast<xns::ubyte*>      (static_cast<void*>      (dst)),
					  static_cast<const xns::ubyte*>(static_cast<const void*>(src)),
					  size * sizeof(D));
	}

}

#endif // MEMMOVE_HEADER
