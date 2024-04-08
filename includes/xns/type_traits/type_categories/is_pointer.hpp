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

#ifndef XNS_IS_POINTER_HEADER
#define XNS_IS_POINTER_HEADER

#include "xns/type_traits/type_trait_constants/integral_constant.hpp"
#include "xns/type_traits/type_modifications/remove_cv.hpp"
#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  P O I N T E R --------------------------------------------------

	namespace ___impl {

		/* is pointer */
		template <typename ___type>
		struct ___is_pointer : public xns::false_type {
			___xns_not_instantiable(___is_pointer);
		};

		/* pointer specialisation */
		template <typename ___type>
		struct ___is_pointer<___type*> : public xns::true_type {
			___xns_not_instantiable(___is_pointer);
		};

		/* helper */
		template<typename ___type>
		struct ___is_pointer_helper final : public ___impl::___is_pointer<xns::remove_cv<___type>> {
			___xns_not_instantiable(___is_pointer_helper);
		};

	} // namespace ___impl


	/* is pointer */
	template<typename ___type>
	concept is_pointer = xns::___impl::___is_pointer_helper<___type>::value;

} // namespace xns

#endif // XNS_IS_POINTER_HEADER
