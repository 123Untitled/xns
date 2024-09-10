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

#ifndef XNS_INDEX_OF_HEADER
#define XNS_INDEX_OF_HEADER

#include "xns/type_traits/relationships_and_property_queries/is_same.hpp"
#include "xns/type_traits/other/is_one_of.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- I N D E X  O F ------------------------------------------------------

	/* index of */
	template <typename ___type, typename... A>
	consteval auto index_of(void) noexcept -> decltype(sizeof(0)) {

		static_assert(xns::is_one_of<___type, A...>, "___type is not in parameter pack.");

		decltype(sizeof(0)) idx = 0;
		bool found = false;
		((xns::is_same<___type, A> ? found = true : found ? true : ++idx), ...);
		return idx;
	}

} // namespace xns

#endif // XNS_INDEX_OF_HEADER
