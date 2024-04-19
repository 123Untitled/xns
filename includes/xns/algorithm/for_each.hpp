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

#ifndef XNS_FOR_EACH_HEADER
#define XNS_FOR_EACH_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- F O R  E A C H ------------------------------------------------------

	/* for each */
	template <typename ___it, typename ___fn>
	constexpr auto for_each(___it __first, ___it __last, ___fn __f) noexcept -> ___fn {
		for (; __first != __last; ++__first)
			static_cast<void>(__f(*__first));
		return __f;
	}

} // namespace xns

#endif // XNS_FOR_EACH_HEADER
