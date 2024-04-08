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

#ifndef XNS_RANK_HEADER
#define XNS_RANK_HEADER

#include "xns/config/macros.hpp"
#include "xns/type_traits/type_trait_constants/integral_constant.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R A N K -------------------------------------------------------------

	namespace ___impl {


		/* rank */
		template <typename ___type>
		struct ___rank final : public xns::integral_constant<decltype(sizeof(0)), 0> {
			___xns_not_instantiable(___rank);
		};

		/* rank unbounded array */
		template <typename ___type>
		struct ___rank<___type[]> final : public xns::integral_constant<decltype(sizeof(0)), ___rank<___type>::value + 1> {
			___xns_not_instantiable(___rank);
		};

		/* rank bounded array */
		template <typename ___type, decltype(sizeof(0)) ___size>
		struct ___rank<___type[___size]> final : public xns::integral_constant<decltype(sizeof(0)), ___rank<___type>::value + 1> {
			___xns_not_instantiable(___rank);
		};

	} // namespace ___impl


	/* rank */
	template <typename ___type>
	constexpr decltype(sizeof(0)) rank = xns::___impl::___rank<___type>::value;

} // namespace xns

#endif // XNS_RANK_HEADER
