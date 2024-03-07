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

#include "config.hpp"

// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

#if not XNS_HAS_BUILTIN(__is_trivially_constructible)
#	error "compiler does not support __is_trivially_constructible"
#endif

	// -- I S  T R I V I A L L Y  D E F A U L T  C O N S T R U C T I B L E ----

	/* is trivially default constructible */
	template <typename T>
	concept is_trivially_default_constructible = __is_trivially_constructible(T);

} // namespace xns

#endif // XNS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP
