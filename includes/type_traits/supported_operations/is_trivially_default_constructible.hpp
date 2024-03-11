/*****************************************************************************/
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*****************************************************************************/

#pragma once

#ifndef XNS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP
#define XNS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP

#include "is_trivially_constructible.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  T R I V I A L L Y  D E F A U L T  C O N S T R U C T I B L E ----

	/* is trivially default constructible */
	template <typename T>
	concept is_trivially_default_constructible = xns::is_trivially_constructible<T>;

	/* are trivially default constructible */
	template <typename... T>
	concept are_trivially_default_constructible = (xns::is_trivially_default_constructible<T> and ...);

} // namespace xns

#endif // XNS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP
