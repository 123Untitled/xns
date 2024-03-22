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

#ifndef XNS_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_HEADER
#define XNS_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_HEADER

#include "type_traits/supported_operations/is_trivially_constructible.hpp"
#include "type_traits/type_modifications/add_lvalue_reference.hpp"
#include "type_traits/type_modifications/add_const.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  T R I V I A L L Y  C O P Y  C O N S T R U C T I B L E ----------

	/* is trivially copy constructible */
	template <typename T>
	concept is_trivially_copy_constructible
		= xns::is_trivially_constructible<T, xns::add_lvalue_reference<xns::add_const<T>>>;

	/* are trivially copy constructible */
	template <typename... T>
	concept are_trivially_copy_constructible
		= (xns::is_trivially_copy_constructible<T> && ...);

} // namespace xns

#endif // XNS_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_HEADER
