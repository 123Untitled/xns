#ifndef XNS_AS_CONST_HPP
#define XNS_AS_CONST_HPP

#include "xns/add_const.hpp"

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A S  C O N S T -------------------------------------------------------

	/* as const */
	template <typename T>
	inline constexpr auto as_const(T& t) noexcept -> xns::add_const<T>& {
		return t;
	}

	/* as const */
	template <typename T>
	void as_const(const T&&) = delete;

} // namespace xns

#endif // XNS_AS_CONST_HPP
