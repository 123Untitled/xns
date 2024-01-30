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

#ifndef XNS_ADD_RVALUE_REFERENCE_HPP
#define XNS_ADD_RVALUE_REFERENCE_HPP

#include "is_referenceable.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A D D  R V A L U E  R E F E R E N C E ---------------------------------

	#if __has_builtin(__add_rvalue_reference)
	template <typename T>
	using add_rvalue_reference = __add_rvalue_reference(T);
	#endif

} // namespace xns

#endif // XNS_ADD_RVALUE_REFERENCE_HPP
