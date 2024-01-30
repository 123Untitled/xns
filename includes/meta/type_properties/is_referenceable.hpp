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

#ifndef XNS_IS_REFERENCEABLE_HPP
#define XNS_IS_REFERENCEABLE_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  R E F E R E N C E A B L E --------------------------------------

	#if __has_builtin(__is_referenceable)
	template <typename T>
	concept is_referenceable = __is_referenceable(T);
	#endif

} // namespace xns

#endif // XNS_IS_REFERENCEABLE_HPP
