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

#ifndef XNS_LIFECYCLE_HEADER
#define XNS_LIFECYCLE_HEADER

#include "xns/config/macros.hpp"

#include "xns/type_traits/type_operations/move.hpp"
#include "xns/type_traits/type_operations/forward.hpp"

#include "xns/type_traits/type_modifications/remove_const.hpp"
#include "xns/type_traits/type_transformations/remove_cvref.hpp"

#include "xns/type_traits/supported_operations/is_constructible.hpp"
#include "xns/type_traits/supported_operations/is_default_constructible.hpp"
#include "xns/type_traits/supported_operations/is_copy_constructible.hpp"
#include "xns/type_traits/supported_operations/is_move_constructible.hpp"

#include "xns/type_traits/supported_operations/is_destructible.hpp"
#include "xns/type_traits/supported_operations/is_trivially_destructible.hpp"

#include "xns/type_traits/supported_operations/is_nothrow_default_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_copy_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_move_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_constructible.hpp"
#include "xns/type_traits/supported_operations/is_nothrow_destructible.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- L I F E C Y C L E ---------------------------------------------------

	template <typename ___type>
	class lifecycle final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self       = xns::lifecycle<___type>;

			/* value type */
			using value_type = ___type;

			/* pointer type */
			using pointer    = value_type*;
			//using pointer    = xns::remove_const<value_type>*;


			// -- public lifecycle --------------------------------------------

			/* non-instantiable class */
			___xns_not_instantiable(lifecycle);


			// -- public static methods ---------------------------------------

			// default construct
			/**
			 * @fn construct
			 * @brief default constructs an object in a storage
			 * @param p pointer
			*/
			static constexpr auto construct(pointer ___p)
				noexcept(xns::is_nothrow_default_constructible<value_type>) -> void {
				static_assert(xns::is_default_constructible<value_type>,
						"lifecycle, type is not default constructible");
				::new((void*)___p) value_type{};
			}

			// copy construct
			/**
			 * @fn construct
			 * @brief copy constructs an object in a storage
			 * @param p pointer
			 * @param value value
			*/
			static constexpr auto construct(pointer ___p, const value_type& ___value)
				noexcept(xns::is_nothrow_copy_constructible<value_type>) -> void {
				static_assert(xns::is_copy_constructible<value_type>,
						"lifecycle, type is not copy constructible");
				::new((void*)___p) value_type{___value};
			}

			// move construct
			/**
			 * @fn construct
			 * @brief move constructs an object in a storage
			 * @param p pointer
			 * @param value value
			*/
			static constexpr auto construct(pointer ___p, value_type&& ___value)
				noexcept(xns::is_nothrow_move_constructible<value_type>) -> void {
				static_assert(xns::is_move_constructible<value_type>,
						"lifecycle, type is not move constructible");
				::new((void*)___p) value_type{xns::move(___value)};
			}

			// forward construct
			/**
			 * @fn construct
			 * @brief constructs an object in a storage with forwarded arguments
			 * @param p pointer
			 * @param args arguments
			*/
			template <typename... ___params> requires (sizeof...(___params) > 1
												   || (sizeof...(___params) == 1
												   && xns::are_not_same<value_type, xns::remove_cvref<___params>...>))
			static constexpr auto construct(pointer ___p, ___params&&... ___args)
				noexcept(xns::is_nothrow_constructible<value_type, ___params...>) -> void {
				static_assert(xns::is_constructible<value_type, ___params...>,
						"lifecycle, type is not constructible with given arguments");
				// use () to construct to let implicit conversion work
				::new((void*)___p) value_type(xns::forward<___params>(___args)...);
			}

			// destroy
			/**
			 * @fn destroy
			 * @brief destructs an object in a storage
			 * @param p pointer
			*/
			static constexpr void destroy(pointer ___p) noexcept {

				// check if type is trivially destructible
				if constexpr (xns::is_trivially_destructible<value_type>)
					return;
				else {

					// check if type throws on destruction
					static_assert(xns::is_nothrow_destructible<value_type>,
						"lifecycle, requires type to be nothrow destructible");

					// check type is destructible
					static_assert(xns::is_destructible<value_type>,
							"lifecycle, type is not destructible");

					___p->~value_type();
				}
			}

	}; // class lifecycle

} // namespace xns

#endif // XNS_LIFECYCLE_HEADER
