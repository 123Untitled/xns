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

#ifndef XNS_INTEGRAL_CONSTANT_HEADER
#define XNS_INTEGRAL_CONSTANT_HEADER

#include "xns/config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I N T E G R A L  C O N S T A N T ------------------------------------

	/* integral constant */
	template <typename ___type, ___type ___vl>
	struct integral_constant {


		// -- types -----------------------------------------------------------

		/* self type */
		using self = xns::integral_constant<___type, ___vl>;

		/* value type */
		using value_type = ___type;


		// -- static members --------------------------------------------------

		/* value */
		static constexpr value_type value = ___vl;


		// -- conversion operators --------------------------------------------

		/* value_type conversion operator */
		consteval operator value_type() const noexcept {
			return value;
		}


		// -- function call operator ------------------------------------------

		/* function call operator */
		consteval auto operator()() const noexcept -> value_type {
			return value;
		}

	}; // struct integral_constant


	/* bool constant */
	template <bool ___vl>
	using bool_constant = xns::integral_constant<bool, ___vl>;

	/* true type */
	using true_type = xns::bool_constant<true>;

	/* false type */
	using false_type = xns::bool_constant<false>;

} // namespace xns

#endif // XNS_INTEGRAL_CONSTANT_HEADER
