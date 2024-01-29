#ifndef XNS_DECAY_HPP
#define XNS_DECAY_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- D E C A Y -----------------------------------------------------------

	template <typename T>
	struct decay final {

		using type = xns::remove_reference<T>;



} // namespace xns

#endif // XNS_DECAY_HPP
