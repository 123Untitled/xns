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


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  V O L A T I L E  -----------------------------------------------


	namespace __impl {

		/* is volatile */
		template <typename __type>
		struct is_volatile                  : xns::false_type  {
		};

		/* specialization */
		template <typename __type>
		struct is_volatile<volatile __type> : xns::true_type {
		};

	} // namespace __impl


	/* is const concept */
	template <typename __type>
	concept is_volatile = xns::__impl::is_volatile<__type>::value;

} // namespace xns

#endif // XNS_IS_VOLATILE_HEADER
