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

#ifndef XNS_ADD_LVALUE_REFERENCE_HEADER
#define XNS_ADD_LVALUE_REFERENCE_HEADER

#include "xns/type_traits/type_properties/is_referenceable.hpp"
#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A D D  L V A L U E  R E F E R E N C E -------------------------------

	namespace ___impl {


		/* add lvalue reference */
		template <typename, bool>
		struct ___add_lvalue_reference;

		/* false specialisation */
		template <typename ___type>
		struct ___add_lvalue_reference<___type, false> final {
			using type = ___type;
			___xns_not_instantiable(___add_lvalue_reference);
		};

		/* true specialisation */
		template <typename ___type>
		struct ___add_lvalue_reference<___type, true> final {
			using type = ___type&;
			___xns_not_instantiable(___add_lvalue_reference);
		};

	} // namespace ___impl


	/* add lvalue reference */
	template <typename ___type>
	using add_lvalue_reference = typename xns::___impl::___add_lvalue_reference<___type,
																				xns::is_referenceable<___type>>::type;

} // namespace xns

#endif // XNS_ADD_LVALUE_REFERENCE_HEADER
