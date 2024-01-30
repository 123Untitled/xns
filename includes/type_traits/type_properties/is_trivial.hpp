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

#ifndef XNS_IS_TRIVIAL_HPP
#define XNS_IS_TRIVIAL_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  T R I V I A L --------------------------------------------------

	/* is trivial */
	template <typename T>
	concept is_trivial = __is_trivial(T);

	/* are trivial */
	template <typename... T>
	concept are_trivial = (xns::is_trivial<T> && ...);

} // namespace xns

#endif // XNS_IS_TRIVIAL_HPP
