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

#ifndef XNS_IS_BOUNDED_ARRAY_HEADER
#define XNS_IS_BOUNDED_ARRAY_HEADER

#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  B O U N D E D  A R R A Y ---------------------------------------

	namespace ___impl {


		/* is bounded array */
		template <typename ___type>
		struct ___is_bounded_array final {
			___xns_not_instantiable(___is_bounded_array);
			static constexpr bool value = false;
		};

		/* is bounded array bounded specialization */
		template <typename ___type, decltype(sizeof(0)) ___size>
		struct ___is_bounded_array<___type[___size]> final {
			___xns_not_instantiable(___is_bounded_array);
			static constexpr bool value = true;
		};

	} // namespace ___impl


	/* is bounded array */
	template <typename ___type>
	concept is_bounded_array = ___impl::___is_bounded_array<___type>::value;

} // namespace xns

#endif // XNS_IS_BOUNDED_ARRAY_HEADER
