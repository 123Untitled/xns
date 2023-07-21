#ifndef INDEX_OF_HEADER
#define INDEX_OF_HEADER

#include "is_same.hpp"
#include "types.hpp"
#include "is_one_of.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- I N D E X  O F ------------------------------------------------------

	/* index of */
	template <class T, class... A>
	consteval xns::size_t index_of(void) {

		static_assert(xns::is_one_of<T, A...>, "TYPE NOT IN PACK");

		xns::size_t idx = 0;
		bool found = false;
		((xns::is_same<T, A> ? found = true : found ? true : ++idx), ...);
		return idx;
	}



}

#endif
