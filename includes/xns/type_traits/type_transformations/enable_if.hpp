/*****************************************************************************/
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*****************************************************************************/

#pragma once

#ifndef XNS_ENABLE_IF_HEADER
#define XNS_ENABLE_IF_HEADER

#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- E N A B L E  I F ----------------------------------------------------

	namespace ___impl {


		/* enable if */
		template <bool, typename ___type = void>
		struct ___enable_if final {
			___xns_not_instantiable(___enable_if);
		};

		/* true specialization */
		template <typename ___type>
		struct ___enable_if<true, ___type> final {
			using type = ___type;
			___xns_not_instantiable(___enable_if);
		};

	} // namespace ___impl


	/* enable if */
	template <bool ___cond, typename ___type = void>
	using enable_if = typename xns::___impl::___enable_if<___cond, ___type>::type;

} // namespace xns

#endif // XNS_ENABLE_IF_HEADER
