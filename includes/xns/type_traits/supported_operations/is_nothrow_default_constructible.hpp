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

#ifndef XNS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_HEADER
#define XNS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_HEADER

#include "xns/type_traits/supported_operations/is_nothrow_constructible.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  N O T H R O W  D E F A U L T  C O N S T R U C T I B L E --------

	/* is nothrow default constructible */
	template <typename ___type>
	concept is_nothrow_default_constructible
		= xns::is_nothrow_constructible<___type>;

	/* are nothrow default constructible */
	template <typename... ___types>
	concept are_nothrow_default_constructible
		= (xns::is_nothrow_default_constructible<___types> && ...);

} // namespace xns

#endif // XNS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_HEADER
