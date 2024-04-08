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

#ifndef XNS_IS_CONST_HEADER
#define XNS_IS_CONST_HEADER

#include "xns/config/macros.hpp"
#include "xns/type_traits/type_modifications/remove_reference.hpp"
#include "xns/type_traits/type_trait_constants/integral_constant.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C O N S T ------------------------------------------------------

	namespace ___impl {

		/* is const */
		template <typename ___type>
		struct ___is_const final : public xns::false_type {
			___xns_not_instantiable(___is_const);
		};

		/* const specialization */
		template <typename ___type>
		struct ___is_const<const ___type> final : public xns::true_type {
			___xns_not_instantiable(___is_const);
		};

	} // namespace ___impl


	/* is const */
	template <typename ___type>
	concept is_const = xns::___impl::___is_const<xns::remove_reference<___type>>::value;

} // namespace xns

#endif // XNS_IS_CONST_HEADER
