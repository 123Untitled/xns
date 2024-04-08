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

#ifndef XNS_IS_REFERENCE_HEADER
#define XNS_IS_REFERENCE_HEADER

#include "xns/type_traits/type_categories/is_lvalue_reference.hpp"
#include "xns/type_traits/type_categories/is_rvalue_reference.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  R E F E R E N C E ----------------------------------------------

	/* is reference */
	template <typename ___type>
	concept is_reference = (xns::is_lvalue_reference<___type>
						 || xns::is_rvalue_reference<___type>);

} // namespace xns

#endif // XNS_IS_REFERENCE_HEADER
