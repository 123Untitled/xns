#ifndef XNS_INDEX_OF_HEADER
#define XNS_INDEX_OF_HEADER

#include "is_same.hpp"
#include "types.hpp"
#include "is_one_of.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- I N D E X  O F ------------------------------------------------------

	/* index of */
	template <typename T, typename... A>
	consteval auto index_of(void) noexcept -> xns::size_t {

		static_assert(xns::is_one_of<T, A...>, "(xns::index_of) T is not in parameter pack.");

		xns::size_t idx = 0;
		bool found = false;
		((xns::is_same<T, A> ? found = true : found ? true : ++idx), ...);
		return idx;
	}



}

#endif
