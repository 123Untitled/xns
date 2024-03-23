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

#ifndef XNS_MAKE_SIGNED_HEADER
#define XNS_MAKE_SIGNED_HEADER

#include "xns/type_traits/types.hpp"

#include "xns/type_traits/type_categories/is_bool.hpp"
#include "xns/type_traits/type_categories/is_enum.hpp"
#include "xns/type_traits/type_categories/is_integral.hpp"
#include "xns/type_traits/type_properties/is_const.hpp"
#include "xns/type_traits/type_properties/is_volatile.hpp"

#include "xns/type_traits/type_transformations/conditional.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- M A K E  S I G N E D ------------------------------------------------

	namespace __impl {


		template <typename __type>
		class make_signed final {


			// -- assertions --------------------------------------------------

			// check if __type is an integral type
			static_assert(xns::is_integral<__type> || xns::is_enum<__type>,
					"make_signed requires an integral type.");

			// check if __type is not a bool
			static_assert(xns::is_bool<__type> == false,
					"make_signed does not support bool.");


			private:

				// -- private types -------------------------------------------

				/* signed type */
				using __stype = xns::sint<sizeof(__type) * xns::bits_per_byte>;


			public:

				// -- public types --------------------------------------------

				/* conditional type */
				using type = xns::conditional<xns::is_const<__type>,
							 xns::conditional<xns::is_volatile<__type>,
											  const volatile __stype,
											  const __stype>,
							 xns::conditional<xns::is_volatile<__type>,
											  volatile __stype,
											  __stype>>;

		}; // struct make_signed

	} // namespace __impl


	/* make signed */
	template <typename __type>
	using make_signed = typename xns::__impl::make_signed<__type>::type;

} // namespace xns

#endif // XNS_MAKE_SIGNED_HEADER
