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

#ifndef XNS_REMOVE_POINTER_HEADER
#define XNS_REMOVE_POINTER_HEADER

#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- R E M O V E  P O I N T E R ------------------------------------------

	namespace ___impl {


		/* remove pointer */
		template <typename ___type>
		struct ___remove_pointer final {
			using type = ___type;
			___xns_not_instantiable(___remove_pointer);
		};

		/* pointer specialization */
		template <typename ___type>
		struct ___remove_pointer<___type*> final {
			using type = ___type;
			___xns_not_instantiable(___remove_pointer);
		};

		/* const pointer specialization */
		template <typename ___type>
		struct ___remove_pointer<___type* const> final {
			using type = ___type;
			___xns_not_instantiable(___remove_pointer);
		};

		/* volatile pointer specialization */
		template <typename ___type>
		struct ___remove_pointer<___type* volatile> final {
			using type = ___type;
			___xns_not_instantiable(___remove_pointer);
		};

		/* const volatile pointer specialization */
		template <typename ___type>
		struct ___remove_pointer<___type* const volatile> final {
			using type = ___type;
			___xns_not_instantiable(___remove_pointer);
		};

	} // namespace ___impl


	/* remove pointer */
	template <typename ___type>
	using remove_pointer = typename xns::___impl::___remove_pointer<___type>::type;

} // namespace xns

#endif // XNS_REMOVE_POINTER_HEADER
