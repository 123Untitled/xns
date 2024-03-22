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

#include "config/macros.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- I N T E G R A L  C O N S T A N T ------------------------------------

	/* integral constant */
	template <typename T, T V>
	struct integral_constant {


		// -- types -----------------------------------------------------------

		/* self type */
		using self = xns::integral_constant<T, V>;

		/* value type */
		using value_type = T;


		// -- static members --------------------------------------------------

		/* value */
		static constexpr value_type value{V};


		// -- conversion operators --------------------------------------------

		/* value_type conversion operator */
		inline consteval operator value_type() const noexcept {
			return value;
		}


		// -- function call operator ------------------------------------------

		/* function call operator */
		inline consteval auto operator()() const noexcept -> value_type {
			return value;
		}

	}; // struct integral_constant


	/* bool constant */
	template <bool B>
	using bool_constant = xns::integral_constant<bool, B>;


	// -- T R U E  T Y P E -----------------------------------------------------

	/* true type */
	using true_type = xns::bool_constant<true>;


	// -- F A L S E  T Y P E ---------------------------------------------------

	/* false type */
	using false_type = xns::bool_constant<false>;

} // namespace xns

#endif // XNS_INTEGRAL_CONSTANT_HEADER
