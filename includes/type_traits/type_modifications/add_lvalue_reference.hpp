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

#ifndef XNS_ADD_LVALUE_REFERENCE_HEADER
#define XNS_ADD_LVALUE_REFERENCE_HEADER

#include "is_referenceable.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A D D  L V A L U E  R E F E R E N C E -------------------------------

	// -- detail --------------------------------------------------------------

	namespace impl {

		// -- forward declarations --------------------------------------------

		/* add lvalue reference */
		template <typename, bool>
		struct add_lvalue_reference;

		/* add lvalue reference false specialisation */
		template <typename T>
		struct add_lvalue_reference<T, false> final {

			// -- types -------------------------------------------------------

			/* type */
			using type = T;

			// -- lifecycle ---------------------------------------------------

			/* not instantiable */
			XNS_NOT_INSTANTIABLE(add_lvalue_reference);

		};

		/* add lvalue reference true specialisation */
		template <typename T>
		struct add_lvalue_reference<T, true> final {

			// -- types -------------------------------------------------------

			/* type */
			using type = T&;

			// -- lifecycle ---------------------------------------------------

			/* not instantiable */
			XNS_NOT_INSTANTIABLE(add_lvalue_reference);

		};

	} // namespace impl

	/* add lvalue reference */
	template <typename T>
	using add_lvalue_reference = typename impl::add_lvalue_reference<T, xns::is_referenceable<T>>::type;

} // namespace xns

#endif // XNS_ADD_LVALUE_REFERENCE_HEADER
