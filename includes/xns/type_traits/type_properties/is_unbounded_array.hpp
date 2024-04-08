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

#ifndef XNS_IS_UNBOUNDED_ARRAY_HEADER
#define XNS_IS_UNBOUNDED_ARRAY_HEADER

#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  U N B O U N D E D  A R R A Y -----------------------------------

	namespace ___impl {


		/* is unbounded array */
		template <typename ___type>
		struct ___is_unbounded_array final {
			___xns_not_instantiable(___is_unbounded_array);
			static constexpr bool value = false;
		};

		/* is unbounded array unbounded specialization */
		template <typename ___type>
		struct ___is_unbounded_array<___type[]> final {
			___xns_not_instantiable(___is_unbounded_array);
			static constexpr bool value = true;
		};

	} // namespace ___impl


	/* is unbounded array */
	template <typename ___type>
	concept is_unbounded_array = ___impl::___is_unbounded_array<___type>::value;

} // namespace xns

#endif // XNS_IS_UNBOUNDED_ARRAY_HEADER
