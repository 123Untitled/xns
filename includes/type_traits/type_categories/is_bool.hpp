#ifndef XNS_IS_BOOL_HPP
#define XNS_IS_BOOL_HPP

#include "is_same.hpp"
#include "remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  B O O L ----------------------------------------------------------

	/* is bool */
	template <typename T>
	constexpr bool is_bool = xns::is_same<bool, xns::remove_cv<T>>;

} // namespace xns

#endif // XNS_IS_BOOL_HPP
