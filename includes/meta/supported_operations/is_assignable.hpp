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

#ifndef XNS_IS_ASSIGNABLE_HPP
#define XNS_IS_ASSIGNABLE_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  A S S I G N A B L E --------------------------------------------

	/* is assignable */
	template <typename T, typename U>
	concept is_assignable = __is_assignable(T, U);

} // namespace xns

#endif // XNS_IS_ASSIGNABLE_HPP


/*
template <class T, class U>
concept is_assignable = requires(T t) {
	{ t = xns::declval<U>() } -> xns::is_convertible<T&>;
};
*/


