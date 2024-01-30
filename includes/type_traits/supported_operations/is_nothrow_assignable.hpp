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

#ifndef IS_NOTHROW_ASSIGNABLE_HPP
#define IS_NOTHROW_ASSIGNABLE_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  N O T H R O W  A S S I G N A B L E -----------------------------

	/* is nothrow assignable */
	template <typename T, typename A>
	concept is_nothrow_assignable = __is_nothrow_assignable(T, A);

} // namespace xns

#endif // IS_NOTHROW_ASSIGNABLE_HPP
