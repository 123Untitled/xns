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

#ifndef XNS_IS_EMPTY_BASE_HPP
#define XNS_IS_EMPTY_BASE_HPP

#include "is_empty.hpp"
#include "is_final.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  E M P T Y  B A S E ----------------------------------------------

	/* is empty base */
	template <typename T>
	concept is_empty_base = xns::is_empty<T> && not xns::is_final<T>;

} // namespace xns

#endif // XNS_IS_EMPTY_BASE_HPP
