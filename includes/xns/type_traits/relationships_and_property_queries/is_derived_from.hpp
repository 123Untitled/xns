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
#include "xns/type_traits/type_modifications/remove.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  D E R I V E D  F R O M -----------------------------------------

	namespace __impl {

		template <typename __derived, typename __base>
		struct is_derived_from {


			private:

				// -- private static methods ----------------------------------

				/* test for derived */
				static consteval auto __test(__base*) -> xns::true_type;

				/* test for not derived */
				static consteval auto __test(...)     -> xns::false_type;


			public:

				// -- public static constants ---------------------------------

				/* value */
				static constexpr bool value = decltype(__test(static_cast<__derived*>(nullptr)))::value;

		}; // struct is_derived_from

	} // namespace __impl


	/* is derived from */
	template <typename __derived, typename __base>
	concept is_derived_from = __impl::is_derived_from<__derived, __base>::value;

} // namespace xns

#endif // XNS_IS_BASE_OF_HEADER
