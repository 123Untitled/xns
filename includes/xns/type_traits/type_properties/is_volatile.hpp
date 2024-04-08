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

#ifndef XNS_IS_VOLATILE_HEADER
#define XNS_IS_VOLATILE_HEADER

#include "xns/type_traits/type_trait_constants/integral_constant.hpp"
#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  V O L A T I L E ------------------------------------------------

	namespace ___impl {


		/* is volatile */
		template <typename ___type>
		struct ___is_volatile final : xns::false_type  {
			___xns_not_instantiable(___is_volatile);
		};

		/* volatile specialization */
		template <typename ___type>
		struct ___is_volatile<volatile ___type> : xns::true_type {
			___xns_not_instantiable(___is_volatile);
		};

	} // namespace __impl


	/* is volatile */
	template <typename ___type>
	concept is_volatile = xns::___impl::___is_volatile<___type>::value;

} // namespace xns

#endif // XNS_IS_VOLATILE_HEADER
