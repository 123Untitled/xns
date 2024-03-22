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

#ifndef XNS_ADD_RVALUE_REFERENCE_HEADER
#define XNS_ADD_RVALUE_REFERENCE_HEADER

#include "type_traits/type_properties/is_referenceable.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A D D  R V A L U E  R E F E R E N C E -------------------------------


	namespace impl {

		// -- forward declarations --------------------------------------------

		/* add rvalue reference */
		template <typename, bool>
		struct add_rvalue_reference;

		/* add rvalue reference false specialisation */
		template <typename T>
		struct add_rvalue_reference<T, false> final {

			// -- types -------------------------------------------------------

			/* type */
			using type = T;

			// -- lifecycle ---------------------------------------------------

			/* not instantiable */
			XNS_NOT_INSTANTIABLE(add_rvalue_reference);

		};

		/* add rvalue reference true specialisation */
		template <typename T>
		struct add_rvalue_reference<T, true> final {

			// -- types -------------------------------------------------------

			/* type */
			using type = T&&;

			// -- lifecycle ---------------------------------------------------

			/* not instantiable */
			XNS_NOT_INSTANTIABLE(add_rvalue_reference);

		};

	} // namespace impl

	/* add rvalue reference */
	template <typename T>
	using add_rvalue_reference = typename impl::add_rvalue_reference<T, xns::is_referenceable<T>>::type;

} // namespace xns

#endif // XNS_ADD_RVALUE_REFERENCE_HEADER
