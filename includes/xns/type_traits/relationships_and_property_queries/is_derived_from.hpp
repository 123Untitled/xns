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

#ifndef XNS_IS_DERIVED_FROM_HEADER
#define XNS_IS_DERIVED_FROM_HEADER

#include "xns/type_traits/type_trait_constants/integral_constant.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  D E R I V E D  F R O M -----------------------------------------

	namespace ___impl {


		/* is derived from */
		template <typename ___derived, typename ___base>
		struct ___is_derived_from {


			private:

				// -- private static methods ----------------------------------

				/* test for derived */
				static consteval auto test(___base*) noexcept -> xns::true_type;

				/* test for not derived */
				static consteval auto test(...) noexcept -> xns::false_type;


			public:

				// -- public static constants ---------------------------------

				/* value */
				static constexpr bool value = decltype(test(static_cast<___derived*>(nullptr)))::value;

		};

	} // namespace __impl


	/* is derived from */
	template <typename ___derived, typename ___base>
	concept is_derived_from = xns::___impl::___is_derived_from<___derived, ___base>::value;

} // namespace xns

#endif // XNS_IS_BASE_OF_HEADER
