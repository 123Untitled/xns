#ifndef CONDITIONAL_HEADER
#define CONDITIONAL_HEADER


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- C O N D I T I O N A L -----------------------------------------------

	/* conditional */
	template <bool B, class T, class F>
	struct conditional                   { using type = T; };

	/* conditional for false */
	template <class T, class F>
	struct conditional<false, T, F>      { using type = F; };

	/* conditional type */
	template <bool B, class T, class F>
	using conditional_t = typename conditional<B, T, F>::type;

	/* conditional value */
	template <bool B, class T, class F>
	static constexpr bool conditional_v = conditional<B, T, F>::value;

	/* conditional concept */
	template <bool B, class T, class F>
	concept conditional_c = conditional_v<B, T, F>;

}

#endif


