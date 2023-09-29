#ifndef XNS_STRNCMP_HEADER
#define XNS_STRNCMP_HEADER

// local headers
#include "types.hpp"
#include "is_char.hpp"
#include "type_compare.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S T R N C M P -------------------------------------------------------

	/* strncmp */
	template <typename A, typename B>
	constexpr auto strncmp(const A* a, const B* b, xns::size_t size) noexcept -> int {
		// check A and B are character types
		static_assert(xns::is_char<A> && xns::is_char<B>,
			"): STRNCMP: requires character types :(");
		// get bigger type
		using bigger = xns::bigger<A, B>;
		// loop over characters
		while (--size
			&& (*a != static_cast<A>(0))
			&& (*b != static_cast<B>(0))
			&& (static_cast<bigger>(*a) == static_cast<bigger>(*b))) {
			// increment pointers
			++a; ++b;
		} // return difference
		return static_cast<bigger>(*a) < static_cast<bigger>(*b) ? -1
			 : static_cast<bigger>(*a) > static_cast<bigger>(*b) ?  1 : 0;
	}

}

#endif // STRNCMP_HEADER
