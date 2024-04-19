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

#ifndef XNS_ALIGNMENT_OF_HEADER
#define XNS_ALIGNMENT_OF_HEADER


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A L I G N M E N T  O F ----------------------------------------------

	/* alignment of */
	template <typename ___type>
	constexpr auto alignment_of = alignof(___type);

} // namespace xns

#endif // XNS_ALIGNMENT_OF_HEADER