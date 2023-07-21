#ifndef UNIT_TESTS_HPP
#define UNIT_TESTS_HPP

#include <iostream>
#include <iomanip>
#include <chrono>
#include <climits>

#include "string_literal.hpp"

#include "testclass.hpp"
#include "color.hpp"
#include "escape.hpp"


namespace UT {


	/* print start message */
	template <xns::string_literal test>
	void start_ut(void) {
		std::cout << "\n\nSTARTING UNIT TEST: \x1b[33m" << test.data() << "\x1b[0m\n" << std::endl;
	}

	template <xns::hexcolor color, class... A>
	void print(A&&... args) {
		xns::string c = xns::escape::hex_color(color);
		std::cout << c.data();
		(std::cout << ... << args);
		xns::string r = xns::escape::reset_style();
		std::cout << r.data() << std::flush;
	}

	/* print message */
	template <xns::string_literal msg>
	void print(void) {
		std::cout << "\x1b[33m" << msg.data() << "\x1b[0m" << std::endl;
	}

	/* unit test template [specialized in .cpp files] */
	template <xns::string_literal>
	bool unit_tests(void);


	// -- detail --------------------------------------------------------------

	namespace impl {

		template <xns::string_literal test, xns::string_literal... rest>
		bool dispatcher(void) {
			// start ut
			start_ut<test>();
			// test current unit test
			if (!unit_tests<test>()) { return false; }

			// check if there are more unit tests
			if constexpr (sizeof...(rest) > 0) { return dispatcher<rest...>(); }

			return true;
		}
	}


	/* unit test dispatcher */
	template <xns::string_literal... LT>
	bool dispatcher(void) {
		// check if there are unit tests
		static_assert(sizeof...(LT) > 0, "): NO UNIT TESTS TO RUN :(");
		// return true if all unit tests succeed
		return impl::dispatcher<LT...>();
	}


	/* unit test launcher */
	inline void launcher(void) {
		UT::dispatcher<

			// "window", (infinitely loops)

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

			"meta",


			"numeric_limits",


			"unique_ptr" // actually segfaults




		>();
	}


};


#endif
