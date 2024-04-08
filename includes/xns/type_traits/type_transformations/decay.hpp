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

#ifndef XNS_DECAY_HEADER
#define XNS_DECAY_HEADER

#include "xns/type_traits/type_modifications/add_pointer.hpp"
#include "xns/type_traits/type_modifications/remove_extent.hpp"
#include "xns/type_traits/type_categories/is_array.hpp"
#include "xns/type_traits/type_categories/is_function.hpp"
#include "xns/type_traits/type_transformations/conditional.hpp"
#include "xns/type_traits/type_modifications/remove_cv.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- D E C A Y -----------------------------------------------------------

	// -- detail --------------------------------------------------------------

	namespace impl {

		/* decay */
		template <typename T>
		using type = xns::conditional<xns::is_array<T>,
									 xns::add_pointer<xns::remove_extent<T>>,
									 xns::conditional<xns::is_function<T>,
													  xns::add_pointer<T>,
													  xns::remove_cv<T>>>;

	} // namespace impl


	/* decay */
	template <typename T>
	using decay = impl::type<xns::remove_reference<T>>;

} // namespace xns

#endif // XNS_DECAY_HEADER
