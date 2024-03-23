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

#ifndef XNS_IS_NOTHROW_COPY_CONSTRUCTIBLE_HEADER
#define XNS_IS_NOTHROW_COPY_CONSTRUCTIBLE_HEADER

#include "xns/type_traits/type_modifications/add_const.hpp"
#include "xns/type_traits/type_modifications/add_lvalue_reference.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_constructible.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  N O T H R O W  C O P Y  C O N S T R U C T I B L E --------------

	/* is nothrow copy constructible */
	template <typename T>
	concept is_nothrow_copy_constructible
		= xns::is_nothrow_constructible<T, xns::add_lvalue_reference<xns::add_const<T>>>;

	/* are nothrow copy constructible */
	template <typename... T>
	concept are_nothrow_copy_constructible
		= (xns::is_nothrow_copy_constructible<T> && ...);

} // namespace xns

#endif // XNS_IS_NOTHROW_COPY_CONSTRUCTIBLE_HPP
