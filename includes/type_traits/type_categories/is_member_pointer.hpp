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

#ifndef XNS_IS_MEMBER_POINTER_HEADER
#define XNS_IS_MEMBER_POINTER_HEADER

#include "type_traits/type_modifications/remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- detail --------------------------------------------------------------

	namespace impl {

		/* is member pointer */
		template <typename T>
		constexpr bool is_member_pointer = false;

		/* specialisation */
		template <typename T, typename U>
		constexpr bool is_member_pointer<T U::*> = true;

	} // namespace impl


	// -- I S  M E M B E R  P O I N T E R -------------------------------------

	/* is member pointer concept */
	template<class T>
	concept is_member_pointer = impl::is_member_pointer<xns::remove_cv<T>>;

} // namespace xns

#endif // XNS_IS_MEMBER_POINTER_HPP
