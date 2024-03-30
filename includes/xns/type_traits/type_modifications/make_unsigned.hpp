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

#ifndef XNS_MAKE_UNSIGNED_HEADER
#define XNS_MAKE_UNSIGNED_HEADER

#include "xns/type_traits/types.hpp"

#include "xns/type_traits/type_categories/is_bool.hpp"
#include "xns/type_traits/type_categories/is_enum.hpp"
#include "xns/type_traits/type_categories/is_integral.hpp"
#include "xns/type_traits/type_properties/is_const.hpp"
#include "xns/type_traits/type_properties/is_volatile.hpp"

#include "xns/type_traits/type_transformations/conditional.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M A K E  U N S I G N E D --------------------------------------------

	namespace ___impl {


		template <typename __type>
		class make_unsigned final {


			// -- assertions --------------------------------------------------

			// check if __type is an integral type
			static_assert(xns::is_integral<__type> || xns::is_enum<__type>,
					"make_unsigned requires an integral type");

			// check if __type is not a bool
			static_assert(xns::is_bool<__type> == false,
					"make_unsigned does not support bool");


			private:

				// -- private types -------------------------------------------

				/* signed type */
				using __utype = xns::uint<sizeof(__type) * xns::bits_per_byte>;


			public:

				// -- public types --------------------------------------------

				/* conditional type */
				using type = xns::conditional<xns::is_const<__type>,
							 xns::conditional<xns::is_volatile<__type>,
											  const volatile __utype,
											  const __utype>,
							 xns::conditional<xns::is_volatile<__type>,
											  volatile __utype,
											  __utype>>;

		}; // class make_unsigned

	} // namespace __impl


	/* make unsigned */
	template <typename ___type>
	using make_unsigned = typename xns::___impl::make_unsigned<___type>::type;

} // namespace xns

#endif // XNS_MAKE_UNSIGNED_HPP
