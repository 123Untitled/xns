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

#ifndef XNS_IS_SAME_HEADER
#define XNS_IS_SAME_HEADER

#include "xns/type_traits/type_modifications/remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  S A M E ---------------------------------------------------------

	// -- detail --------------------------------------------------------------

	namespace impl {


		template <typename T, typename U>
		constexpr bool is_same_test       = false;

		template <typename T>
		constexpr bool is_same_test<T, T> = true;

		template <typename T, typename... U>
		constexpr bool is_same = (xns::impl::is_same_test<T, U> && ...);

	} // namespace impl


	/* is same concept */
	template <typename... T>
	concept is_same = xns::impl::is_same<T...>;

	/* is not same concept */
	template <typename... T>
	concept is_not_same = not xns::impl::is_same<T...>;

	/* is same remove cvr concept */
	template <typename... T>
	concept is_same_cvr = xns::impl::is_same<xns::remove_cvr<T>...>;


} // namespace xns

#endif // XNS_IS_SAME_HEADER
