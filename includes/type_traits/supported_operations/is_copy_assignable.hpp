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

#ifndef XNS_IS_COPY_ASSIGNABLE_HPP
#define XNS_IS_COPY_ASSIGNABLE_HPP

#include "is_assignable.hpp"
#include "add_lvalue_reference.hpp"
#include "add_const.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C O P Y  A S S I G N A B L E -----------------------------------

	/* is copy assignable */
	template <typename T>
	concept is_copy_assignable
		= xns::is_assignable<xns::add_lvalue_reference<T>,
							 xns::add_lvalue_reference<xns::add_const<T>>>;

	/* are copy assignable */
	template <typename... T>
	concept are_copy_assignable = (xns::is_copy_assignable<T> && ...);

} // namespace xns

#endif // XNS_IS_COPY_ASSIGNABLE_HPP
