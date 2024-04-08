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

#ifndef XNS_REMOVE_VOLATILE_HEADER
#define XNS_REMOVE_VOLATILE_HEADER

#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E M O V E  V O L A T I L E ----------------------------------------

	namespace ___impl {


		/* remove volatile */
		template <typename ___type>
		struct ___remove_volatile final {
			using type = ___type;
			___xns_not_instantiable(___remove_volatile);
		};

		/* volatile specialization */
		template <typename ___type>
		struct ___remove_volatile<volatile ___type> final {
			using type = ___type;
			___xns_not_instantiable(___remove_volatile);
		};

	} // namespace ___impl


	/* remove volatile */
	template <typename ___type>
	using remove_volatile = typename xns::___impl::___remove_volatile<___type>::type;

} // namespace xns

#endif // XNS_REMOVE_VOLATILE_HEADER
