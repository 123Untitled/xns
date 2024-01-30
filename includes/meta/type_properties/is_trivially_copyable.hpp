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

#ifndef XNS_IS_TRIVIALLY_COPYABLE_HPP
#define XNS_IS_TRIVIALLY_COPYABLE_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  T R I V I A L L Y  C O P Y A B L E -----------------------------

	/* is trivially copyable */
	template <typename T>
	concept is_trivially_copyable = __is_trivially_copyable(T);

	/* are trivially copyable */
	template <typename... T>
	concept are_trivially_copyable = (xns::is_trivially_copyable<T> && ...);

} // namespace xns

#endif // XNS_IS_TRIVIALLY_COPYABLE_HPP
