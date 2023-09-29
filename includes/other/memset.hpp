#ifndef XNS_MEMSET_HEADER
#define XNS_MEMSET_HEADER

// local headers
#include "types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// man:
	// void* memset(void *b, int c, size_t len);


	// -- M E M S E T ---------------------------------------------------------

	/* memset */
	template <typename T>
	inline auto memset(T* dst, const T& value, const xns::size_t size) -> void {
		// loop over bytes
		for (xns::size_t i = 0; i < size; ++i)
			// copy byte
			dst[i] = value;
	}



}

#endif // MEMSET_HEADER
