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

#ifndef XNS_DECLVAL_HEADER
#define XNS_DECLVAL_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- D E C L V A L -------------------------------------------------------

	namespace ___impl {

		template <typename ___type>
		auto declval(int) noexcept -> ___type&&;

		template <typename ___type>
		auto declval(long) noexcept -> ___type;
	}

	/* declval */
	template <typename ___type>
	auto declval(void) noexcept -> decltype(___impl::declval<___type>(0));

} // namespace xns

#endif // XNS_DECLVAL_HEADER
