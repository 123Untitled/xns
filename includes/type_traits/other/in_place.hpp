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

#ifndef XNS_IN_PLACE_HPP
#define XNS_IN_PLACE_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I N  P L A C E --------------------------------------------------------

	// disambiguation tag for in place construction

	/* in place */
	struct in_place final {
		explicit in_place(void) noexcept = default;
	};

	/* in place type */
	template <typename T>
	struct in_place_type final {
		explicit in_place_type(void) noexcept = default;
	};

	/* in place index */
	template <decltype(sizeof(0)) I>
	struct in_place_index final {
		explicit in_place_index(void) noexcept = default;
	};

} // namespace xns

#endif // XNS_IN_PLACE_HPP
