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

#ifndef XNS_IS_REFERENCEABLE_HEADER
#define XNS_IS_REFERENCEABLE_HEADER

#include "xns/type_traits/type_trait_constants/integral_constant.hpp"
#include "xns/type_traits/relationships_and_property_queries/is_same.hpp"
#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- detail --------------------------------------------------------------

	namespace impl {

		/* is referenceable */
		struct is_referenceable final {

			// -- lifecycle ---------------------------------------------------

			/* not instantiable */
			XNS_NOT_INSTANTIABLE(is_referenceable);


			// -- static methods ----------------------------------------------

			/* test */
			template <typename T>
			static auto test(int) noexcept -> T&;

			/* test */
			template <typename T>
			static auto test(...) noexcept -> xns::false_type;

		}; // struct is_referenceable

	} // namespace impl


	/* is referenceable */
	template <typename T>
	concept is_referenceable = not xns::is_same<
							   decltype(impl::is_referenceable::test<T>(0)),
							   xns::false_type>;

} // namespace xns

#endif // XNS_IS_REFERENCEABLE_HEADER
