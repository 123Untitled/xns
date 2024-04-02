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

#ifndef XNS_IS_INVOCABLE_HEADER
#define XNS_IS_INVOCABLE_HEADER

#include <concepts>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  I N V O C A B L E ----------------------------------------------

	/* is invocable */
	template <typename __func, typename... __params>
	concept is_invocable = std::is_invocable_v<__func, __params...>;

	/* is invocable r */
	template <typename __ret, typename __func, typename... __params>
	concept is_invocable_r = std::is_invocable_r_v<__ret, __func, __params...>;


} // namespace xns

#endif // XNS_IS_INVOCABLE_HEADER
