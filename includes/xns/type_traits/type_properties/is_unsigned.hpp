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

#ifndef XNS_IS_UNSIGNED_HEADER
#define XNS_IS_UNSIGNED_HEADER

#include "xns/config/macros.hpp"
#include "xns/type_traits/type_categories/is_integral.hpp"
#include "xns/type_traits/type_categories/is_arithmetic.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  U N S I G N E D ------------------------------------------------

	namespace ___impl {


		/* integral specialization */
		template <typename ___type, bool = xns::is_integral<___type>>
		struct ___is_unsigned_impl : public xns::bool_constant<(___type(-1) > ___type(0))> {
			___xns_not_instantiable(___is_unsigned_impl);
		};

		/* floating point specialization */
		template <typename ___type>
		struct ___is_unsigned_impl<___type, false> : public xns::false_type {
			___xns_not_instantiable(___is_unsigned_impl);
		};

		/* arithmetic specialization */
		template <typename ___type, bool = xns::is_arithmetic<___type>>
		struct ___is_unsigned_arithmetic : public ___is_unsigned_impl<___type> {
			___xns_not_instantiable(___is_unsigned_arithmetic);
		};

		/* non arithmetic specialization */
		template <typename ___type>
		struct ___is_unsigned_arithmetic<___type, false> : public xns::false_type {
			___xns_not_instantiable(___is_unsigned_arithmetic);
		};

		/* is unsigned */
		template <typename ___type>
		struct ___is_unsigned final : public ___is_unsigned_arithmetic<___type> {
			___xns_not_instantiable(___is_unsigned);
		};

	} // namespace ___impl


	/* is unsigned */
	template <typename ___type>
	concept is_unsigned = xns::___impl::___is_unsigned<___type>::value;

	/* is unsigned integral */
	template <typename ___type>
	concept is_unsigned_integral = xns::is_unsigned<___type> && xns::is_integral<___type>;

} // namespace xns

#endif // XNS_IS_UNSIGNED_HEADER
