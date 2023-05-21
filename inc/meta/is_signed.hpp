#ifndef IS_SIGNED_HEADER
#define IS_SIGNED_HEADER

#include "types.hpp"
#include "integral_constant.hpp"
#include "enable_if.hpp"
#include "remove.hpp"
#include "is_integral.hpp"

// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {

	// -- I S  S I G N E D ----------------------------------------------------


	/* is signed */
	template <class T>
	struct is_signed   : public xns::integral_constant<bool, (T(-1) < T(0))> {};

	/* is signed value */
	template <class T>
	inline constexpr bool is_signed_v = is_signed<xns::remove_cv<T>>::value;

	/* is signed concept */
	template <class T>
	concept is_signed_c = Xf::is_signed_v<T>;

	/* enable for signed */
	//template <typename T>
	//using enable_if_signed = enable_if_t<is_signed<T>::value, T>;


	// -- I S  U N S I G N E D ------------------------------------------------

	/* is unsigned */
	template <class T>
	struct is_unsigned : public xns::integral_constant<bool, (T(-1) > T(0))> {};

	/* is unsigned value */
	template <class T>
	inline constexpr bool is_unsigned_v = is_unsigned<T>::value;

	/* is unsigned concept */
	template <class T>
	concept is_unsigned_c = Xf::is_unsigned_v<T>;

	/* enable for unsigned */
	//template <class T>
	//using enable_if_unsigned = enable_if_t<is_unsigned<T>::value, T>;


	// -- I S  I N T E G R A L  S I G N E D -----------------------------------

	template <class T>
	concept is_signed_integral_c = Xf::is_signed_v<T> && xns::is_integral<T>;


	// -- I S  I N T E G R A L  U N S I G N E D -------------------------------

	template <class T>
	concept is_unsigned_integral_c = Xf::is_unsigned_v<T> && xns::is_integral<T>;


}






#endif
