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

#ifndef XNS_IS_CONSTRUCTIBLE_HPP
#define XNS_IS_CONSTRUCTIBLE_HPP

#include "declval.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  C O N S T R U C T I B L E --------------------------------------

	/* is constructible */
	template <typename T, typename... A>
	concept is_constructible = __is_constructible(T, A...);


	///* is constructible concept */
	//template <class T, class... A>
	//concept is_constructible = requires {
	//	T(xns::declval<A>()...);
	//};
	//
	///* is copy constructible concept (no implicit conversion) */
	//template <class T, class... A>
	//concept is_constructible_strict = requires {
	//	T{xns::declval<A>()...};
	//};




} // namespace xns

#endif // IS_CONSTRUCTIBLE_HPP
