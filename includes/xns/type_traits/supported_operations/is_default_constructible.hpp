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

#ifndef IS_DEFAULT_CONSTRUCTIBLE_HEADER
#define IS_DEFAULT_CONSTRUCTIBLE_HEADER

#include "xns/type_traits/supported_operations/is_constructible.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  D E F A U L T  C O N S T R U C T I B L E -----------------------

	/* is default constructible */
	template <typename T>
	concept is_default_constructible = xns::is_constructible<T>;

	/* are default constructible */
	template <typename... T>
	concept are_default_constructible = (xns::is_default_constructible<T> && ...);

} // namespace xns

#endif // IS_DEFAULT_CONSTRUCTIBLE_HEADER
