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

#ifndef XNS_REMOVE_CONST_HEADER
#define XNS_REMOVE_CONST_HEADER

#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E M O V E  C O N S T ----------------------------------------------

	namespace ___impl {


		/* remove const */
		template <typename ___type>
		struct ___remove_const final {
			using type = ___type;
			___xns_not_instantiable(___remove_const);
		};

		/* const specialization */
		template <typename ___type>
		struct ___remove_const<const ___type> final {
			using type = ___type;
			___xns_not_instantiable(___remove_const);
		};

	}; // namespace ___impl


	/* remove const */
	template <typename ___type>
	using remove_const = typename xns::___impl::___remove_const<___type>::type;

} // namespace xns

#endif // XNS_REMOVE_CONST_HEADER
