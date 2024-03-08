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

#ifndef XNS_ADD_LVALUE_REFERENCE_HPP
#define XNS_ADD_LVALUE_REFERENCE_HPP

#include "config.hpp"
#include "is_referenceable.hpp"

#if not XNS_HAS_BUILTIN(__add_lvalue_reference)
#	include <type_traits>
#endif


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {

#if not XNS_HAS_BUILTIN(__add_lvalue_reference)

	/* add lvalue reference */
	template <typename T>
	using add_lvalue_reference = std::add_lvalue_reference<T>;

#else

	// -- A D D  L V A L U E  R E F E R E N C E -------------------------------

	/* add lvalue reference */
	template <typename T>
	using add_lvalue_reference = __add_lvalue_reference(T);

#endif

} // namespace xns

#endif // XNS_ADD_LVALUE_REFERENCE_HPP
