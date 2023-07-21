#ifndef CONDITIONAL_HEADER
#define CONDITIONAL_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- C O N D I T I O N A L -----------------------------------------------

	/* conditional */
	template <bool B, class T, class F>
	struct _conditional;

	/* true specialization */
	template <class T, class F>
	struct _conditional<true, T, F>       { using type = T; };

	/* false specialization */
	template <class T, class F>
	struct _conditional<false, T, F>      { using type = F; };

	/* conditional type */
	template <bool B, class T, class F>
	using conditional = typename _conditional<B, T, F>::type;

}


#endif


