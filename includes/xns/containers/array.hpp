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

	template <typename ___type, xns::size_t ___size>
	class array final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = xns::array<___type, ___size>;

			/* array type */
			using ___array = ___type[___size];


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type      = ___type;

			/* reference type */
			using reference       = value_type&;

			/* const reference type */
			using const_reference = const value_type&;

			/* pointer type */
			using pointer         = value_type*;

			/* const pointer type */
			using const_pointer   = const value_type*;

			/* size type */
			using size_type       = decltype(___size);


			// -- public members ----------------------------------------------

			/* data */
			___array _data;


			// -- public subscript operators ----------------------------------

			/* subscript operator */
			constexpr auto operator[](const size_type i) noexcept -> reference {
				return _data[i];
			}

			/* const subscript operator */
			constexpr auto operator[](const size_type i) const noexcept -> const_reference {
				return _data[i];
			}


			// -- public accessors --------------------------------------------

			/* size */
			constexpr auto size(void) const noexcept -> size_type {
				return ___size;
			}

			/* data */
			constexpr auto data(void) noexcept -> pointer {
				return _data;
			}

			/* const data */
			constexpr auto data(void) const noexcept -> const_pointer {
				return _data;
			}

			/* c array */
			constexpr auto c_array(void) noexcept -> ___array& {
				return _data;
			}

			/* const c array */
			constexpr auto c_array(void) const noexcept -> const ___array& {
				return _data;
			}

	}; // class array


	// -- deduction guides ----------------------------------------------------

	/* variadic constructor */
	template <typename... ___params>
	array(___params&&...) -> array<xns::common_type<___params...>, sizeof...(___params)>;

} // namespace xns

#endif // XNS_ARRAY_HEADER
