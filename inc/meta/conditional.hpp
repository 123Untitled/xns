#ifndef CONDITIONAL_HEADER
#define CONDITIONAL_HEADER


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- C O N D I T I O N A L -----------------------------------------------

	/* conditional */
	template <bool B, class T, class F>
	struct conditional;

	/* conditional for true */
	template <class T, class F>
	struct conditional<true, T, F>       { using type = T; };

	/* conditional for false */
	template <class T, class F>
	struct conditional<false, T, F>      { using type = F; };

	/* conditional type */
	template <bool B, class T, class F>
	using conditional_t = typename conditional<B, T, F>::type;


}

#endif


