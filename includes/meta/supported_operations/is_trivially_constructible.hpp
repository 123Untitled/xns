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

#ifndef XNS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
#define XNS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  T R I V I A L L Y  C O N S T R U C T I B L E -------------------

	/* is trivially constructible */
	template <typename T, typename... A>
	concept is_trivially_constructible = __is_trivially_constructible(T, A...);

} // namespace xns

#endif // XNS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
