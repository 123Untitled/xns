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

#ifndef XNS_LAZY_CONDITIONAL_HEADER
#define XNS_LAZY_CONDITIONAL_HEADER

#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- L A Z Y  C O N D I T I O N A L --------------------------------------

	namespace ___impl {


		/* lazy conditional */
		template <bool, typename, template <typename...>
								  typename, typename...>
		struct lazy_conditional;


		/* false specialisation */
		template <typename ___default, template <typename...>
									   typename ___op, typename... ___params>
		struct lazy_conditional<false, ___default, ___op, ___params...> final {
			using type = ___default;
			___xns_not_instantiable(lazy_conditional);
		};

		/* true specialisation */
		template <typename ___default, template <typename...>
									   typename ___op, typename... ___params>
		struct lazy_conditional<true, ___default, ___op, ___params...> final {
			using type = ___op<___params...>;
			___xns_not_instantiable(lazy_conditional);
		};

	} // namespace ___impl


	/* lazy conditional */
	template<bool ___cond, typename ___default, template<typename...>
												typename ___op, typename... ___params>
	using lazy_conditional = typename xns::___impl::lazy_conditional<___cond,
																	 ___default,
																	 ___op,
																	 ___params...>::type;

} // namespace xns

#endif // XNS_LAZY_CONDITIONAL_HEADER
