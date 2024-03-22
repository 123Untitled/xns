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

#ifndef XNS_FORWARD_HEADER
#define XNS_FORWARD_HEADER

#include "type_traits/other/to_reference.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

	// input        param        result
	// T&           &            T&
	// T&           &&           T&
	// T&&          &            T&
	// T&&          &&           T&&


	// -- F O R W A R D -------------------------------------------------------

	// forward lvalues as lvalues
	template <typename T>
	inline constexpr auto forward(xns::to_lvalue<T> obj) noexcept -> T&& {
		// cast -> T& && = T&
		return static_cast<T&&>(obj);
	}

	// forward rvalues as rvalues
	template <typename T>
	inline constexpr auto forward(xns::to_rvalue<T> obj) noexcept -> T&& {
		// cast -> T&& && = T&&
		return static_cast<T&&>(obj);
	}

	template <typename T>
	inline constexpr auto forward2(xns::to_lvalue<T> obj) noexcept -> xns::to_lvalue<T> {
		return static_cast<xns::to_lvalue<T>>(obj);
	}

	template <typename T>
	inline constexpr auto forward2(xns::to_rvalue<T> obj) noexcept -> xns::to_lvalue<T> {
		return static_cast<xns::to_lvalue<T>>(obj);
	}

}

#endif
