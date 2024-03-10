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

#include "integral_constant.hpp"
#include "is_same.hpp"
#include "macros.hpp"


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
