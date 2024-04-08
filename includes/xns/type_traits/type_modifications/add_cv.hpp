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

#ifndef XNS_ADD_CV_HEADER
#define XNS_ADD_CV_HEADER

#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A D D  C V ----------------------------------------------------------

	namespace ___impl {


		/* add cv */
		template <typename ___type>
		struct ___add_cv final {
			using type = const volatile ___type;
			___xns_not_instantiable(___add_cv);
		};

	} // namespace ___impl


	/* add cv */
	template <typename ___type>
	using add_cv = typename xns::___impl::___add_cv<___type>::type;

} // namespace xns

#endif // XNS_ADD_CV_HEADER
