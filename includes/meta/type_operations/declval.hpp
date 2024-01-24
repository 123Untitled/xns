#ifndef XNS_DECLVAL_HEADER
#define XNS_DECLVAL_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	/* libc++ implementation */

	// -- D E C L V A L -------------------------------------------------------

	namespace impl {

		template <typename T, typename R = T&&>
		auto declval(int) -> R;

		template <typename T>
		auto declval(long) -> T;
	}

	template<typename T>
	auto declval(void) noexcept -> decltype(impl::declval<T>(0));


}

#endif
