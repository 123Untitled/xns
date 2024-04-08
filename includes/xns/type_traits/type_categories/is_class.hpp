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

#include "xns/type_traits/type_categories/is_union.hpp"
#include "xns/type_traits/type_trait_constants/integral_constant.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C L A S S ------------------------------------------------------

	namespace ___impl {


		/* test for class */
		template <typename ___type>
		constexpr auto ___is_class_test(int ___type::*) -> xns::bool_constant<xns::is_union<___type> == false>;

		/* test for non-class */
		template <typename ___type>
		constexpr auto ___is_class_test(...) -> xns::false_type;

	} // namespace ___impl


	/* is class */
	template <typename ___type>
	concept is_class = decltype(xns::___impl::___is_class_test<___type>(nullptr))::value;

} // namespace xns

#endif // XNS_IS_CLASS_HEADER
