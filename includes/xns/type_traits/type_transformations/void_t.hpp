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

#ifndef XNS_VOID_T_HEADER
#define XNS_VOID_T_HEADER

#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- V O I D  T ----------------------------------------------------------

	namespace ___impl {


		/* void_t */
		template <typename...>
		struct ___void_t final {
			using type = void;
			___xns_not_instantiable(___void_t);
		};

	} // namespace ___impl


	/* void_t */
	template <typename... ___types>
	using void_t = typename xns::___impl::___void_t<___types...>::type;

} // namespace xns

#endif // XNS_VOID_T_HEADER
