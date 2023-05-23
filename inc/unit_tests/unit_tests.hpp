#ifndef UNIT_TESTS_HPP
#define UNIT_TESTS_HPP

#include <iostream>
#include <iomanip>
#include <chrono>
#include <climits>

#include "xns.hpp"
#include "testclass.hpp"

#define START_UT(msg) std::cout << "\n\nSTARTING UNIT TEST: \x1b[33m" << msg << "\x1b[0m\n" << std::endl;

namespace UT {


	bool meta_ut(void);

	void tuple_ut(void);

	void string_ut(void);

	void window_ut(void);

	void numeric_limits_ut(void);

	void unique_pointer_ut(void);

	void array_ut(void);


};


#endif
