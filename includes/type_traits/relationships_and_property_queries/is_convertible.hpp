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

#ifndef XNS_IS_CONVERTIBLE_HEADER
#define XNS_IS_CONVERTIBLE_HEADER

// local headers
#include "type_traits/type_operations/declval.hpp"
#include "type_traits/relationships_and_property_queries/is_same.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C O N V E R T I B L E ------------------------------------------

	namespace __impl {


		/* is convertible */
		template <typename __from, typename __to>
		concept is_convertible = requires {
			requires xns::is_same<__to, decltype(static_cast<__to>(xns::declval<__from>()))>;
		};

	} // namespace __impl

	/* is convertible */
	template <typename __from, typename __to>
	concept is_convertible = __impl::is_convertible<__from, __to>;

} // namespace xns

#endif // IS_CONVERTIBLE_HEADER
