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

#ifndef XNS_IS_DESTRUCTIBLE_HEADER
#define XNS_IS_DESTRUCTIBLE_HEADER

#include "xns/config/macros.hpp"

#include "xns/type_traits/type_categories/is_function.hpp"
#include "xns/type_traits/type_categories/is_reference.hpp"
#include "xns/type_traits/type_categories/is_void.hpp"
#include "xns/type_traits/type_operations/declval.hpp"
#include "xns/type_traits/type_modifications/remove_all_extents.hpp"
#include "xns/type_traits/type_properties/is_unbounded_array.hpp"
#include "xns/type_traits/type_trait_constants/integral_constant.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  D E S T R U C T I B L E ----------------------------------------

	namespace ___impl {


		/* is destructible */
		template <typename ___type>
		class ___is_destructible final {


			private:

				// -- private structs -----------------------------------------

				/* is destructible test */
				template <typename ___tp>
				struct ___is_destructible_test final {

					/* helper */
					template <typename>
					struct ___helper final {
						___xns_not_instantiable(___helper);
						using type = int;
					};

					___xns_not_instantiable(___is_destructible_test);

					/* test */
					template <typename ___>
					static /* consteval */ constexpr auto ___test(typename ___helper<decltype(xns::declval<___&>().~___())>::type) -> xns::true_type;

					/* test */
					template <typename>
					static /* consteval */ constexpr auto ___test(...) -> xns::false_type;

					/* value */
					static constexpr bool value = decltype(___test<___tp>(0))::value;

				}; // struct ___is_destructible_test

				/* is destructible other */
				template <typename, bool>
				struct ___is_destructible_other;

				/* is destructible other */
				template <typename ___tp>
				struct ___is_destructible_other<___tp, true> : public xns::false_type {
					___xns_not_instantiable(___is_destructible_other);
				};

				/* is destructible other */
				template <typename ___tp>
				struct ___is_destructible_other<___tp, false>
				: public xns::bool_constant<___is_destructible_test<xns::remove_all_extents<___tp>>::value> {
					___xns_not_instantiable(___is_destructible_other);
				};

				/* is destructible reference */
				template <typename, bool>
				struct ___is_destructible_reference;

				/* is destructible reference */
				template <typename ___tp>
				struct ___is_destructible_reference<___tp, true> final : public xns::true_type {
					___xns_not_instantiable(___is_destructible_reference);
				};

				/* is destructible reference */
				template <typename ___tp>
				struct ___is_destructible_reference<___tp, false> final
				: public ___is_destructible_other<___tp,
												  xns::is_void<___tp>
											   || xns::is_function<___tp>
											   || xns::is_unbounded_array<___tp>> {
					___xns_not_instantiable(___is_destructible_reference);
				};


			public:

				/* non-instantiable class */
				___xns_not_instantiable(___is_destructible);


				// -- public constants ----------------------------------------

				/* value */
				static constexpr bool value = ___is_destructible_reference<___type,
														 xns::is_reference<___type>>::value;

		}; // class ___is_destructible

	} // namespace ___impl


	/* is destructible */
	template <typename ___type>
	concept is_destructible = ___impl::___is_destructible<___type>::value;

	/* are destructible */
	template <typename... ___types>
	concept are_destructible = (xns::is_destructible<___types> && ...);

} // namespace xns

#endif // XNS_IS_DESTRUCTIBLE_HEADER
