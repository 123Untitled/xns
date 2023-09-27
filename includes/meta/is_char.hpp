#ifndef IS_CHAR_HEADER
#define IS_CHAR_HEADER

#include "integral_constant.hpp"
#include "remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C H A R  -------------------------------------------------------

	/* false type */
	template <class T>
	struct _is_char_t           : xns::no  {};

	/* true type */
	template <>
	struct _is_char_t<char>     : xns::yes {};

	/* true type */
	template <>
	struct _is_char_t<char8_t>  : xns::yes {};

	/* true type */
	template <>
	struct _is_char_t<char16_t> : xns::yes {};

	/* true type */
	template <>
	struct _is_char_t<char32_t> : xns::yes {};

	/* true type */
	template <>
	struct _is_char_t<wchar_t>  : xns::yes {};


	/* is char concept */
	template <class T>
	concept is_char = _is_char_t<xns::remove_cv<T>>::value;


}


#endif
