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

#ifndef XNS_EXTENT_HEADER
#define XNS_EXTENT_HEADER

#include "xns/type_traits/types.hpp"
#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- E X T E N T ---------------------------------------------------------

	namespace ___impl {


		/* extent for non-array types */
		template <typename ___type, xns::size_t ___dim = 0U>
		struct ___extent final {
			___xns_not_instantiable(___extent);
			static constexpr xns::size_t value = 0;
		};

		/* extent for unbounded array types (first dimension) */
		template <typename ___type>
		struct ___extent<___type[], 0U> final {
			___xns_not_instantiable(___extent);
			static constexpr xns::size_t value = 0U;
		};

		/* extent for unbounded array types (subsequent dimensions) */
		template <typename ___type, xns::size_t ___dim>
		struct ___extent<___type[], ___dim> final {
			___xns_not_instantiable(___extent);
			static constexpr xns::size_t value = ___impl::___extent<___type, ___dim - 1U>::value;
		};

		/* extent for bounded array types (first dimension) */
		template <typename ___type, xns::size_t ___size>
		struct ___extent<___type[___size], 0U> final {
			___xns_not_instantiable(___extent);
			static constexpr xns::size_t value = ___size;
		};

		/* extent for bounded array types (subsequent dimensions) */
		template <typename ___type, xns::size_t ___size, xns::size_t ___dim>
		struct ___extent<___type[___size], ___dim> final {
			___xns_not_instantiable(___extent);
			static constexpr xns::size_t value = ___impl::___extent<___type, ___dim - 1U>::value;
		};

	} // namespace ___impl


	/* extent */
	template <typename ___type, xns::size_t ___dim = 0U>
	constexpr xns::size_t extent = ___impl::___extent<___type, ___dim>::value;

} // namespace xns

#endif // XNS_EXTENT_HEADER
