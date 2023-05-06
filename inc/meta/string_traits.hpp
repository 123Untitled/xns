#ifndef STRING_TRAITS_HEADER
#define STRING_TRAITS_HEADER

#include "types.hpp"
#include "integral_constant.hpp"
#include "remove.hpp"


// -- N A M E S P A C E -------------------------------------------------------

namespace Xf {


	// -- C H A R A C T E R  T Y P E ------------------------------------------

	/* is char false type */
	template <class T>
	struct is_char_t           : false_t {};

	/* is char true type */
	template <>
	struct is_char_t<char>     : true_t {};

	/* is wchar_t true type */
	template <>
	struct is_char_t<wchar_t>  : true_t {};

	/* is char8_t true type */
	template <>
	struct is_char_t<char8_t>  : true_t {};

	/* is char16_t true type */
	template <>
	struct is_char_t<char16_t> : true_t {};

	/* is char32_t true type */
	template <>
	struct is_char_t<char32_t> : true_t {};


	/* is char concept */
	template <class T>
	concept is_char_c = is_char_t<remove_cv_t<T>>::value;

}

#endif
