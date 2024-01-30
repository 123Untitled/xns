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

#ifndef XNS_IS_TRIVIALLY_ASSIGNABLE_HPP
#define XNS_IS_TRIVIALLY_ASSIGNABLE_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  T R I V I A L L Y  A S S I G N A B L E -------------------------

	/* is trivially assignable */
	template <typename T, typename A>
	concept is_trivially_assignable = __is_trivially_assignable(T, A);

} // namespace xns

#endif // XNS_IS_TRIVIALLY_ASSIGNABLE_HPP
