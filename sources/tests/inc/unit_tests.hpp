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

#ifndef XNS_UNIT_TESTS_HEADER
#define XNS_UNIT_TESTS_HEADER

#include <iostream>


// -- U T  N A M E S P A C E --------------------------------------------------

namespace ut {

	template <bool expected, bool result>
	auto test(const char* msg) -> int {
		constexpr const char* symbol[]{
			"[\x1b[33mv\x1b[0m] ",
			"[\x1b[31mx\x1b[0m] " };
		// valid test
		if constexpr (result == expected) {
			std::cout << symbol[0] << msg << std::endl;
			return 0;
		}
		// invalid test
		else {
			std::cout << symbol[1] << msg <<
				" -> (expected: " << expected << ", result: " << result << ")" << std::endl;
			return -1;
		}
	}

} // namespace ut

#endif // XNS_UNIT_TESTS_HEADER
