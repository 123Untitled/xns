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

#ifndef XNS_ADD_VOLATILE_HEADER
#define XNS_ADD_VOLATILE_HEADER

#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A D D  V O L A T I L E ----------------------------------------------

	namespace ___impl {


		/* add volatile */
		template <typename ___type>
		struct ___add_volatile final {
			using type = volatile ___type;
			___xns_not_instantiable(___add_volatile);
		};

	} // namespace ___impl


	/* add volatile */
	template <typename ___type>
	using add_volatile = typename xns::___impl::___add_volatile<___type>::type;

} // namespace xns

#endif // XNS_ADD_VOLATILE_HEADER
