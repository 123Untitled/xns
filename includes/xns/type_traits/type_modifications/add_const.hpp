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

#ifndef XNS_ADD_CONST_HEADER
#define XNS_ADD_CONST_HEADER

#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A D D  C O N S T ----------------------------------------------------

	namespace ___impl {


		/* add const */
		template <typename ___type>
		struct ___add_const final {
			using type = const ___type;
			___xns_not_instantiable(___add_const);
		};

	} // namespace ___impl


	/* add const */
	template <typename ___type>
	using add_const = typename xns::___impl::___add_const<___type>::type;

} // namespace xns

#endif // XNS_ADD_CONST_HEADER
