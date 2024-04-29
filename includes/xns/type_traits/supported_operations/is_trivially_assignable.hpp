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

#ifndef XNS_IS_TRIVIALLY_ASSIGNABLE_HEADER
#define XNS_IS_TRIVIALLY_ASSIGNABLE_HEADER

#include "xns/config/config.hpp"

#if not ___xns_has_builtin(__is_trivially_assignable)
#	error "compiler does not support __is_trivially_assignable"
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  T R I V I A L L Y  A S S I G N A B L E -------------------------

	/* is trivially assignable */
	template <typename ___type, typename ___param>
	concept is_trivially_assignable = __is_trivially_assignable(___type, ___param);

} // namespace xns

#endif // XNS_IS_TRIVIALLY_ASSIGNABLE_HEADER
