#ifndef IS_VOID_HEADER
#define IS_VOID_HEADER

#include "integral_constant.hpp"

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- I S  V O I D --------------------------------------------------------

	/* is void false type */
	template <class T>
	struct IsVoid_s : Xf::false_t { };

	/* is void true type */
	template <>
	struct IsVoid_s<void> : Xf::true_t { };

	/* is void value */
	template <class T>
	constexpr bool IsVoid_v = IsVoid_s<T>::value;

	/* is void concept */
	template <class T>
	concept IsVoid = IsVoid_v<T>;

	/* is not void concept */
	template <class T>
	concept IsNotVoid = !IsVoid_v<T>;


}


#endif
