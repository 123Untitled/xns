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

#ifndef XNS_REMOVE_EXTENT_HEADER
#define XNS_REMOVE_EXTENT_HEADER

#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E M O V E  E X T E N T --------------------------------------------

	namespace ___impl {

		/* remove extent */
		template <typename ___type>
		struct ___remove_extent final {
			___xns_not_instantiable(___remove_extent);
			using type = ___type;
		};

		/* array with unknown bound specialization */
		template <typename ___type>
		struct ___remove_extent<___type[]> final {
			___xns_not_instantiable(___remove_extent);
			using type = ___type;
		};

		/* array specialization */
		template <typename ___type, decltype(sizeof(0)) ___size>
		struct ___remove_extent<___type[___size]> final {
			___xns_not_instantiable(___remove_extent);
			using type = ___type;
		};

	} // namespace ___impl


	/* remove extent */
	template <typename ___type>
	using remove_extent = typename ___impl::___remove_extent<___type>::type;

} // namespace xns

#endif // XNS_REMOVE_EXTENT_HEADER
