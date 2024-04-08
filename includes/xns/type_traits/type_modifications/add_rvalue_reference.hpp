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

#include "xns/type_traits/type_properties/is_referenceable.hpp"
#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A D D  R V A L U E  R E F E R E N C E -------------------------------

	namespace ___impl {


		/* add rvalue reference */
		template <typename, bool>
		struct ___add_rvalue_reference;

		/* false specialisation */
		template <typename ___type>
		struct ___add_rvalue_reference<___type, false> final {
			using type = ___type;
			___xns_not_instantiable(___add_rvalue_reference);
		};

		/* true specialisation */
		template <typename ___type>
		struct ___add_rvalue_reference<___type, true> final {
			using type = ___type&&;
			___xns_not_instantiable(___add_rvalue_reference);
		};

	} // namespace ___impl


	/* add rvalue reference */
	template <typename ___type>
	using add_rvalue_reference = typename xns::___impl::___add_rvalue_reference<___type,
																				xns::is_referenceable<___type>>::type;

} // namespace xns

#endif // XNS_ADD_RVALUE_REFERENCE_HEADER
