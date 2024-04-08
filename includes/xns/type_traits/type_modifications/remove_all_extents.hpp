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

#ifndef XNS_REMOVE_ALL_EXTENTS_HEADER
#define XNS_REMOVE_ALL_EXTENTS_HEADER

#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E M O V E  A L L  E X T E N T S -----------------------------------

	namespace ___impl {

		/* remove all extents */
		template <typename ___type>
		struct ___remove_all_extents final {
			___xns_not_instantiable(___remove_all_extents);
			using type = ___type;
		};

		/* array with unknown bound specialization */
		template <typename ___type>
		struct ___remove_all_extents<___type[]> final {
			___xns_not_instantiable(___remove_all_extents);
			using type = typename ___remove_all_extents<___type>::type;
		};

		/* array specialization */
		template <typename ___type, decltype(sizeof(0)) ___size>
		struct ___remove_all_extents<___type[___size]> final {
			___xns_not_instantiable(___remove_all_extents);
			using type = typename ___remove_all_extents<___type>::type;
		};

	} // namespace ___impl


	/* remove all extents */
	template <typename ___type>
	using remove_all_extents = typename ___impl::___remove_all_extents<___type>::type;

} // namespace xns

#endif // XNS_REMOVE_ALL_EXTENTS_HEADER
