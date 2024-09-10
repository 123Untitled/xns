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

#ifndef XNS_ALWAYS_FALSE_HEADER
#define XNS_ALWAYS_FALSE_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A L W A Y S  F A L S E ----------------------------------------------

	namespace ___impl {


		template <typename>
		struct always_false {
			static constexpr bool value = false;
		};

	} // namespace __impl

	template <typename ___type>
	concept always_false = xns::___impl::always_false<___type>::value;

} // namespace xns

#endif // XNS_ALWAYS_FALSE_HEADER
