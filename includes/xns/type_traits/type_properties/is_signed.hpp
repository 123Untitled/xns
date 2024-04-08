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

#ifndef XNS_IS_SIGNED_HEADER
#define XNS_IS_SIGNED_HEADER

#include "xns/config/macros.hpp"
#include "xns/type_traits/type_categories/is_integral.hpp"
#include "xns/type_traits/type_categories/is_arithmetic.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I S  S I G N E D ----------------------------------------------------

	namespace ___impl {


		/* integral specialization */
		template <typename ___type, bool = xns::is_integral<___type>>
		struct ___is_signed_impl : public xns::bool_constant<(___type(-1) < ___type(0))> {
			___xns_not_instantiable(___is_signed_impl);
		};

		/* floating point specialization */
		template <typename _Tp>
		struct ___is_signed_impl<_Tp, false> : public xns::true_type {
			___xns_not_instantiable(___is_signed_impl);
		};

		/* arithmetic specialization */
		template <typename ___type, bool = xns::is_arithmetic<___type>>
		struct ___is_signed_arithmetic : public ___is_signed_impl<___type> {
			___xns_not_instantiable(___is_signed_arithmetic);
		};

		/* non arithmetic specialization */
		template <typename ___type>
		struct ___is_signed_arithmetic<___type, false> : public xns::false_type {
			___xns_not_instantiable(___is_signed_arithmetic);
		};

		/* is signed */
		template <typename ___type>
		struct ___is_signed final : public ___is_signed_arithmetic<___type> {
			___xns_not_instantiable(___is_signed);
		};

	} // namespace ___impl


	/* is signed */
	template <typename ___type>
	concept is_signed = xns::___impl::___is_signed<___type>::value;

	/* is signed integral */
	template <typename ___type>
	concept is_signed_integral = xns::is_signed<___type> && xns::is_integral<___type>;

} // namespace xns

#endif // XNS_IS_SIGNED_HEADER
