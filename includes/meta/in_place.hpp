#ifndef XNS_IN_PLACE_HEADER
#define XNS_IN_PLACE_HEADER

// local headers
#include "types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I N  P L A C E --------------------------------------------------------

	// disambiguation tag for in place construction

	/* in place */
	struct in_place {
		explicit in_place(void) noexcept = default;
	};

	/* in place type */
	template <typename T>
	struct in_place_type {
		explicit in_place_type(void) noexcept = default;
	};

	/* in place index */
	template <xns::size_t T>
	struct in_place_index {
		explicit in_place_index(void) noexcept = default;
	};


};

#endif // IN_PLACE_HEADER
