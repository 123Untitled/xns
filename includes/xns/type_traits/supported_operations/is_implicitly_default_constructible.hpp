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

#ifndef XNS_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_HEADER
#define XNS_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_HEADER

#include "xns/config/macros.hpp"
#include "xns/type_traits/supported_operations/is_default_constructible.hpp"
#include "xns/type_traits/type_trait_constants/integral_constant.hpp"



// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  I M P L I C I T L Y  D E F A U L T  C O N S T R U C T I B L E --

	namespace ___impl {


		/* test */
		template <typename ___type>
		auto ___is_implicitly_default_constructible_test(___type) -> void;

		/* non-implicitly default constructible */
		template <typename ___type, typename = void, bool = xns::is_default_constructible<___type>>
		struct ___is_implicitly_default_constructible : xns::false_type {
			___xns_not_instantiable(___is_implicitly_default_constructible);
		};

		/* default constructible specialization */
		template <typename ___type>
		struct ___is_implicitly_default_constructible<___type,
												decltype(___is_implicitly_default_constructible_test<___type const&>({})),
												true> : xns::true_type {
			___xns_not_instantiable(___is_implicitly_default_constructible);
		};

		/* non-default constructible specialization */
		template <typename ___type>
		struct ___is_implicitly_default_constructible<___type,
												decltype(___is_implicitly_default_constructible_test<___type const&>({})),
												false> : xns::false_type {
			___xns_not_instantiable(___is_implicitly_default_constructible);
		};

	} // namespace ___impl


	/* is implicitly default constructible */
	template <typename ___type>
	concept is_implicitly_default_constructible = xns::___impl::___is_implicitly_default_constructible<___type>::value;

} // namespace xns

#endif // XNS_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_HEADER
