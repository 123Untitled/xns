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

#ifndef XNS_ADD_CONST_HEADER
#define XNS_ADD_CONST_HEADER

#include "config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A D D  C O N S T ----------------------------------------------------

	// -- detail --------------------------------------------------------------

	namespace impl {

		/* add const */
		template <typename T>
		struct add_const          final {
			using type = const T;
			XNS_NOT_INSTANTIABLE(add_const);
		};

		/* specialisation for const T */
		template <typename T>
		struct add_const<const T> final {
			using type = const T;
			XNS_NOT_INSTANTIABLE(add_const);
		};

	} // namespace impl

	/* add const */
	template <class T>
	using add_const = typename impl::add_const<T>::type;

} // namespace xns

#endif // XNS_ADD_CONST_HEADER
