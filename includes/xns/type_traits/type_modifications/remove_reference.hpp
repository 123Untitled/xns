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

#ifndef XNS_REMOVE_REFERENCE_HEADER
#define XNS_REMOVE_REFERENCE_HEADER

#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E M O V E  R E F E R E N C E --------------------------------------

	namespace ___impl {


		/* remove reference */
		template <typename ___type>
		struct ___remove_reference final {
			using type = ___type;
			___xns_not_instantiable(___remove_reference);
		};

		/* lvalue specialization */
		template <typename ___type>
		struct ___remove_reference<___type&> final {
			using type = ___type;
			___xns_not_instantiable(___remove_reference);
		};

		/* rvalue specialization */
		template <typename ___type>
		struct ___remove_reference<___type&&> final {
			using type = ___type;
			___xns_not_instantiable(___remove_reference);
		};

	} // namespace ___impl


	/* remove reference */
	template <typename ___type>
	using remove_reference = typename xns::___impl::___remove_reference<___type>::type;

} // namespace xns

#endif // XNS_REMOVE_REFERENCE_HEADER
