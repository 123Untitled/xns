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

#ifndef XNS_TO_REFERENCE_HEADER
#define XNS_TO_REFERENCE_HEADER

#include "xns/type_traits/type_modifications/remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- T O  L V A L U E  R E F E R E N C E ---------------------------------

	/* forward lvalue helper */
	template <typename T>
	using to_lvalue = xns::remove_reference<T>&;


	// -- T O  R V A L U E  R E F E R E N C E ---------------------------------

	/* forward rvalue helper */
	template <typename T>
	using to_rvalue = xns::remove_reference<T>&&;

} // namespace xns

#endif // XNS_TO_REFERENCE_HEADER
