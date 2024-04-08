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

#ifndef XNS_IS_POLYMORPHIC_HEADER
#define XNS_IS_POLYMORPHIC_HEADER

#include "xns/config/config.hpp"

#if not XNS_HAS_BUILTIN(__is_polymorphic)
#	error "compiler does not support __is_polymorphic"
#endif

#include "xns/type_traits/type_trait_constants/integral_constant.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  P O L Y M O R P H I C ------------------------------------------


	// possible implementation (from cppreference.com), not tested

	namespace ___impl {

		template <typename ___type>
		consteval auto
		___is_polymorphic_test(decltype(dynamic_cast<const volatile void*>(static_cast<___type*>(nullptr))))
		noexcept -> xns::true_type;

		template <typename ___type>
		consteval auto ___is_polymorphic_test(...) noexcept -> xns::false_type;

		template <typename ___type>
		struct ___is_polymorphic final : decltype(xns::___impl::___is_polymorphic_test<___type>(nullptr)) {
		};

	} // namespace ___impl


	/* is polymorphic */
	template <typename ___type>
	concept is_polymorphic = __is_polymorphic(___type);

} // namespace xns

#endif // XNS_IS_POLYMORPHIC_HEADER
