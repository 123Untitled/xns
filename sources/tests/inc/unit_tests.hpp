#ifndef UNIT_TESTS_HPP
#define UNIT_TESTS_HPP

#include <iostream>
#include <iomanip>
#include <chrono>
#include <climits>

#include "string_literal.hpp"

#include "testclass.hpp"
//#include "color.hpp"
//#include "escape.hpp"

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
}

namespace UT {


	/* print start message */
	template <xns::basic_string_literal test>
	void start_ut(void) {
		std::cout << "\n\nSTARTING UNIT TEST: \x1b[33m" << test.data() << "\x1b[0m\n" << std::endl;
	}

	//template <xns::hexcolor color, class... A>
	template <int color, class... A>
	void print(A&&... args) {
		//xns::string c = xns::escape::hex_color(color);
		//std::cout << c.data();
		(std::cout << ... << args);
		//xns::string r = xns::escape::reset_style();
		//std::cout << r.data() << std::flush;
	}

	/* print message */
	template <xns::basic_string_literal msg>
	void print(void) {
		std::cout << "\x1b[33m" << msg.data() << "\x1b[0m" << std::endl;
	}

	/* unit test template [specialized in .cpp files] */
	template <xns::basic_string_literal>
	int unit_tests(void);


	// -- detail --------------------------------------------------------------

	namespace impl {

		template <xns::basic_string_literal test>
		int dispatcher(void) {
			// start ut
			start_ut<test>();
			// test current unit test
			return UT::unit_tests<test>();
		}

		template <xns::basic_string_literal test, xns::basic_string_literal... rest>
		int dispatcher(void) requires (sizeof...(rest) > 0) {
			// start ut
			start_ut<test>();
			// test current unit test
			int ret = UT::unit_tests<test>();
			// test next unit test
			return (ret == 0) ? impl::dispatcher<rest...>() : ret;
		}

	}


	/* unit test dispatcher */
	template <xns::basic_string_literal... LT>
	int dispatch(void) {
		// check if there are unit tests
		static_assert(sizeof...(LT) > 0, "): NO UNIT TESTS TO RUN :(");
		// return true if all unit tests succeed
		return impl::dispatcher<LT...>();
	}


	/* unit test launcher */
	inline int launcher(void) {
		return UT::dispatch<
			"environment",
			"array",
			"string",
			"map",
			"tree",
			"tuple",
			"literal_map",
			"input",
			"random",
			"xorshift",
			"duration",
			"matrix",
			"math",
			"bit_view",
			"path",
			"numeric_limits",
			"unique_ptr" // actually segfaults
			// "window", (infinitely loops)
		>();
	}



}

#endif
