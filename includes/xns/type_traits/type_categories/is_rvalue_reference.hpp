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

#ifndef XNS_IS_RVALUE_REFERENCE_HEADER
#define XNS_IS_RVALUE_REFERENCE_HEADER

#include "xns/type_traits/type_trait_constants/integral_constant.hpp"
#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  R V A L U E  R E F E R E N C E ------------------------------------

	namespace ___impl {

		/* is lvalue reference */
		template <typename ___type>
		struct ___is_rvalue_reference final : public xns::false_type {
			___xns_not_instantiable(___is_rvalue_reference);
		};

		/* lvalue reference specialisation */
		template <typename ___type>
		struct ___is_rvalue_reference<___type&&> final : public xns::true_type {
			___xns_not_instantiable(___is_rvalue_reference);
		};

	} // namespace ___impl


	/* is lvalue reference */
	template <typename ___type>
	concept is_rvalue_reference = xns::___impl::___is_rvalue_reference<___type>::value;

} // namespace xns

#endif // XNS_IS_LVALUE_REFERENCE_HEADER
