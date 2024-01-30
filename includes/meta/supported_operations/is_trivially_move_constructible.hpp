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

#ifndef XNS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_HPP
#define XNS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_HPP

#include "is_trivially_constructible.hpp"
#include "add_rvalue_reference.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  T R I V I A L L Y  M O V E  C O N S T R U C T I B L E ----------

	/* is trivially move constructible */
	template <typename T>
	concept is_trivially_move_constructible =
		xns::is_trivially_constructible<T, xns::add_rvalue_reference<T>>;

	/* are trivially move constructible */
	template <typename... T>
	concept are_trivially_move_constructible = (xns::is_trivially_move_constructible<T> && ...);

} // namespace xns

#endif // XNS_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_HPP
