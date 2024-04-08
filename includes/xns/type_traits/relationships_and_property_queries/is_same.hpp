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

#include "xns/type_traits/type_trait_constants/integral_constant.hpp"
#include "xns/config/config.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  S A M E ---------------------------------------------------------

	namespace ___impl {


		/* is same */
		template <typename ___type, typename ___other>
		struct ___is_same final : xns::false_type {
			___xns_not_instantiable(___is_same);
		};

		/* true specialization */
		template <typename ___type>
		struct ___is_same<___type, ___type> final : xns::true_type {
			___xns_not_instantiable(___is_same);
		};

		template <typename ___type, typename... ___others>
		struct ___are_same final : xns::bool_constant<(___is_same<___type, ___others>::value && ...)> {
			___xns_not_instantiable(___are_same);
		};

	} // namespace ___impl


	/* is same */
	template <typename ___type, typename ___other>
	concept is_same = xns::___impl::___is_same<___type, ___other>::value;

	/* same as */
	template <typename ___type, typename ___other>
	concept same_as = xns::is_same<___type, ___other>;

	/* are same */
	template <typename... ___types>
	concept are_same = xns::___impl::___are_same<___types...>::value;

	/* is not same */
	template <typename ___type, typename ___other>
	concept is_not_same = not xns::is_same<___type, ___other>;

	/* are not same */
	template <typename... ___types>
	concept are_not_same = not xns::are_same<___types...>;

} // namespace xns

#endif // XNS_IS_SAME_HEADER
