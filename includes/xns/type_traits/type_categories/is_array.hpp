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

#ifndef XNS_IS_ARRAY_HEADER
#define XNS_IS_ARRAY_HEADER

#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  A R R A Y ------------------------------------------------------

	namespace ___impl {

		/* is array */
		template <typename ___type>
		struct ___is_array final {
			___xns_not_instantiable(___is_array);
			static constexpr bool value = false;
		};

		/* is array unbounded specialization */
		template <typename ___type>
		struct ___is_array<___type[]> final {
			___xns_not_instantiable(___is_array);
			static constexpr bool value = true;
		};

		/* is array bounded specialization */
		template <typename ___type, decltype(sizeof(0)) ___size>
		struct ___is_array<___type[___size]> final {
			___xns_not_instantiable(___is_array);
			static constexpr bool value = true;
		};

	} // namespace ___impl


	/* is array */
	template <typename ___type>
	concept is_array = ___impl::___is_array<___type>::value;

} // namespace xns

#endif // XNS_IS_ARRAY_HEADER
