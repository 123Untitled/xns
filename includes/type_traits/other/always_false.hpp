#ifndef XNS_ALWAYS_FALSE_HPP
#define XNS_ALWAYS_FALSE_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A L W A Y S  F A L S E ----------------------------------------------

	namespace impl {

		template <typename>
		struct always_false {
			static constexpr bool value = false;
		};
	}

	template <typename T>
	concept always_false = impl::always_false<T>::value;

}

#endif // XNS_ALWAYS_FALSE_HPP