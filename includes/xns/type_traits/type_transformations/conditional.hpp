#ifndef XNS_CONDITIONAL_XNS
#define XNS_CONDITIONAL_XNS


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- C O N D I T I O N A L -----------------------------------------------

	// -- detail --------------------------------------------------------------

	namespace impl {

		/* conditional */
		template <bool, typename T, typename F>
		struct conditional;

		/* true specialization */
		template <typename T, typename F>
		struct conditional<true, T, F>  final { using type = T; };

		/* false specialization */
		template <typename T, typename F>
		struct conditional<false, T, F> final { using type = F; };

	}

	/* conditional */
	template <bool B, typename T, typename F>
	using conditional = typename xns::impl::conditional<B, T, F>::type;

} // namespace xns

#endif // XNS_CONDITIONAL_XNS


