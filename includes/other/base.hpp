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

#ifndef XNS_BASE_HEADER
#define XNS_BASE_HEADER

#include "type_traits/types.hpp"
#include "type_traits/other/is_one_of.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- B A S E -------------------------------------------------------------

	/* hexadecimal base */
	struct hex {
		static constexpr xns::u8 base = 16;
	};

	/* decimal base */
	struct dec {
		static constexpr xns::u8 base = 10;
	};

	/* octal base */
	struct oct {
		static constexpr xns::u8 base = 8;
	};

	/* binary base */
	struct bin {
		static constexpr xns::u8 base = 2;
	};


	// -- I S  B A S E --------------------------------------------------------

	/* is base */
	template <class T>
	concept is_base = xns::is_one_of<T, xns::hex,
										xns::dec,
										xns::oct,
										xns::bin>;


} // namespace xns

#endif // XNS_BASE_HEADER
