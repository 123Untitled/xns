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

#ifndef XNS_IS_CLASS_HEADER
#define XNS_IS_CLASS_HEADER

#include "type_traits/type_categories/is_union.hpp"
#include "type_traits/type_trait_constants/integral_constant.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C L A S S ------------------------------------------------------


	namespace __impl {

		/* test for class */
		template <typename __type>
		constexpr auto test(int __type::*) -> xns::bool_constant<xns::is_union<__type> == false>;

		/* test for non-class */
		template <typename __type>
		constexpr auto test(...) -> xns::false_type;

	}

	/* is_class */
	template <typename __type>
	concept is_class = decltype(xns::__impl::test<__type>(nullptr))::value;

}

#endif
