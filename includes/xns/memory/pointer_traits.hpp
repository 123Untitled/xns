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

#ifndef XNS_POINTER_TRAITS_HEADER
#define XNS_POINTER_TRAITS_HEADER

#include "xns/config/macros.hpp"

#include "xns/type_traits/types.hpp"
#include "xns/memory/addressof.hpp"

#include "xns/type_traits/type_transformations/conditional.hpp"
#include "xns/type_traits/type_transformations/lazy_conditional.hpp"

#include "xns/type_traits/type_properties/have_member_types.hpp"

#include "xns/type_traits/type_categories/is_void.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- P O I N T E R  T R A I T S ------------------------------------------

	template <typename ___ptr>
	class pointer_traits final {

		private:

			// -- private types -----------------------------------------------

			/* ___element */
			template <typename ___type>
			using ___element = typename ___type::element_type;

			/* ___diff */
			template <typename ___type>
			using ___diff = typename ___type::difference_type;


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::pointer_traits<___ptr>;

			/* pointer type */
			using pointer = ___ptr;

			/* element type */
			using element_type = typename ___ptr::element_type;
			/*Ptr::element_type if present;
			otherwise, T if Ptr is a class template specialization Template<T, Args...>, where Args... is zero or more type arguments;
			otherwise, not defined.*/
			// If /*element-type-of*/<Ptr> is not defined, the primary template has no members specified in this page.

			/* difference type */
			using difference_type = xns::lazy_conditional<xns::have_difference_type<___ptr>,
														  xns::ptrdiff_t,
														  ___diff, ___ptr>;

			/* rebind */
			template <typename ___type>
			using rebind = typename ___ptr::template rebind<___type>;
			// otherwise Template<U, Args...> if Ptr is a template specialization Template<T, Args...>


			// -- public lifecycle --------------------------------------------

			/* non-instantiable class */
			___xns_not_instantiable(pointer_traits);

	}; // class pointer_traits


	/* ptr* specialization */
	template <typename ___ptr>
	class pointer_traits<___ptr*> final {

		public:

			// -- public types ------------------------------------------------

			/* pointer type */
			using pointer = ___ptr*;

			/* element type */
			using element_type = ___ptr;

			/* difference type */
			using difference_type = xns::ptrdiff_t;

			/* rebind type */
			template <typename ___type>
			using rebind = ___type*;


			// -- public lifecycle --------------------------------------------

			/* non-instantiable class */
			___xns_not_instantiable(pointer_traits);


			// -- public static methods ---------------------------------------

			/* pointer to */
			static constexpr auto pointer_to(element_type& r) noexcept -> pointer {
				return xns::addressof( r );
			}

			/*
			struct ___nat {};
			static auto pointer_to(xns::conditional<xns::is_void<element_type>, ___nat,
																element_type>& __r) noexcept -> pointer {
				return xns::addressof(__r);
			}
			*/


	}; // class pointer_traits

} // namespace xns

#endif // XNS_POINTER_TRAITS_HEADER
