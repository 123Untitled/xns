#ifndef XNS_TYPE_COMPARE_HEADER
#define XNS_TYPE_COMPARE_HEADER

// local headers
#include "conditional.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- S M A L L E R -------------------------------------------------------

	/* smaller */
	template <typename A, typename B>
	using smaller = xns::conditional<(sizeof(A) < sizeof(B)), A, B>;


	// -- B I G G E R ---------------------------------------------------------

	/* larger */
	template <typename A, typename B>
	using bigger = xns::conditional<(sizeof(A) > sizeof(B)), A, B>;

}

#endif // TYPE_COMPARE_HEADER
