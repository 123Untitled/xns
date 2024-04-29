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

#ifndef XNS_IS_NOTHROW_CONSTRUCTIBLE_HEADER
#define XNS_IS_NOTHROW_CONSTRUCTIBLE_HEADER

#include "xns/type_traits/type_trait_constants/integral_constant.hpp"
#include "xns/type_traits/type_operations/declval.hpp"
#include "xns/type_traits/type_categories/is_reference.hpp"
#include "xns/type_traits/supported_operations/is_constructible.hpp"
#include "xns/type_traits/types.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  N O T H R O W  C O N S T R U C T I B L E -----------------------

	namespace ___impl {


		/* forward declarations */
		template <bool, bool, typename, typename...>
		struct ___is_nothrow_constructible_impl;

		/* test function */
		template <typename ___type>
		auto ___is_nothrow_constructible_test(___type) noexcept -> void {
		}


		/* is not constructible specialization */
		template <typename ___type, bool ___is_ref, typename... ___params>
		struct ___is_nothrow_constructible_impl<false, ___is_ref, ___type, ___params...> : public xns::false_type {
		};

		/* is constructible and not reference specialization */
		template <typename ___type, typename... ___params>
		struct ___is_nothrow_constructible_impl<true, false, ___type, ___params...>
		: public xns::bool_constant<noexcept(___type(xns::declval<___params>()...))> {
		};

		/* is reference specialization */
		template <typename ___type, typename ___param>
		struct ___is_nothrow_constructible_impl<true, true, ___type, ___param>
		: public integral_constant<bool, noexcept(
											___impl::___is_nothrow_constructible_test<___type>(xns::declval<___param>()))> {
		};


		/* is nothrow constructible */
		template <typename ___type, typename... ___params>
		struct ___is_nothrow_constructible final
		: ___impl::___is_nothrow_constructible_impl<xns::is_constructible<___type, ___params...>,
												xns::is_reference<___type>,
												___type, ___params...> {};

		/* array specialization */
		template <typename ___type, xns::size_t ___size>
		struct ___is_nothrow_constructible<___type[___size]> final
		: ___impl::___is_nothrow_constructible_impl<xns::is_constructible<___type>,
									  xns::is_reference<___type>,
									  ___type> {
		};

	} // namespace ___impl


	/* is nothrow constructible */
	template <typename ___type, typename... ___params>
	concept is_nothrow_constructible = ___impl::___is_nothrow_constructible<___type, ___params...>::value;

} // namespace xns

#endif // XNS_IS_NOTHROW_CONSTRUCTIBLE_HEADER
