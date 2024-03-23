/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_IS_CHAR_HEADER
#define XNS_IS_CHAR_HEADER

#include "xns/type_traits/type_trait_constants/integral_constant.hpp"
#include "xns/type_traits/type_modifications/remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C H A R  -------------------------------------------------------

	/* false type */
	template <typename>
	struct _is_char_t           : xns::false_type {};

	/* true type */
	template <>
	struct _is_char_t<char>     : xns::true_type {};

	/* true type */
	template <>
	struct _is_char_t<char8_t>  : xns::true_type {};

	/* true type */
	template <>
	struct _is_char_t<char16_t> : xns::true_type {};

	/* true type */
	template <>
	struct _is_char_t<char32_t> : xns::true_type {};

	/* true type */
	template <>
	struct _is_char_t<wchar_t>  : xns::true_type {};


	/* is char */
	template <typename __type>
	concept is_char = _is_char_t<xns::remove_cv<__type>>::value;


} // namespace xns

#endif // XNS_IS_CHAR_HEADER
