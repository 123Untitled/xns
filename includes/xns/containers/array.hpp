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

#ifndef XNS_ARRAY_HEADER
#define XNS_ARRAY_HEADER

// local headers
#include "xns/type_traits/types.hpp"
#include "xns/type_traits/type_operations/move.hpp"
#include "xns/type_traits/type_transformations/common_type.hpp"
#include "xns/type_traits/type_categories/is_integral.hpp"
#include "xns/type_traits/type_categories/is_enum.hpp"
#include "xns/type_traits/type_categories/is_void.hpp"
#include "xns/type_traits/type_operations/forward.hpp"
#include "xns/type_traits/relationships_and_property_queries/is_convertible.hpp"
#include "xns/utility/swap.hpp"
#include "xns/other/safe_enum.hpp"

#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- A R R A Y -----------------------------------------------------------

	template <typename ___type, decltype(sizeof(0)) ___size>
	class array final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self       = xns::array<___type, ___size>;

			/* value type */
			using value_type = ___type;

			/* mutable reference type */
			using mut_ref    = value_type&;

			/* constant reference type */
			using const_ref  = const value_type&;

			/* mutable pointer type */
			using mut_ptr    = value_type*;

			/* constant pointer type */
			using const_ptr  = const value_type*;

			/* size type */
			using size_type  = decltype(sizeof(0));


			// -- public members ----------------------------------------------

			/* data */
			value_type _data[___size];


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			constexpr auto operator[](const size_type index) noexcept -> mut_ref {
				return _data[index];
			}

			/* const subscript operator */
			constexpr auto operator[](const size_type index) const noexcept -> const_ref {
				return _data[index];
			}


			// -- public accessors --------------------------------------------

			/* size */
			constexpr auto size(void) const noexcept -> size_type {
				return ___size;
			}

			/* data */
			constexpr auto data(void) noexcept -> mut_ptr {
				return _data;
			}

			/* const data */
			constexpr auto data(void) const noexcept -> const_ptr {
				return _data;
			}


	}; // class array


	// -- deduction guides ----------------------------------------------------

	/* variadic constructor */
	template <typename... ___params>
	array(___params&&...) -> array<xns::common_type<___params...>, sizeof...(___params)>;

} // namespace xns

#endif // XNS_ARRAY_HEADER
