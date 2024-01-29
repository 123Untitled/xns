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

#ifndef XNS_ADDRESSOF_HPP
#define XNS_ADDRESSOF_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// -- A D D R E S S O F ---------------------------------------------------

	/* address of */
	template <typename T>
	inline constexpr auto addressof(T& value) noexcept -> T* {
		return __builtin_addressof(value);
	}

} // namespace xns

#endif // XNS_ADDRESSOF_HPP
