#include "unit_tests.hpp"
#include "type_traits/type_categories/is_array.hpp"
#include <iostream>
#include <iomanip>

template <bool expected>
void test(const bool result, const char* msg) {

	// get the boolean as a string
	const char* boolean = result ? "true  " : "false ";

	// print the result
	std::cout   << std::setw(20)
				<< std::right << msg << " "
				<< boolean;

	// print the expected result
	if (result == expected)
		std::cout << "\x1b[32msuccess\x1b[0m" << std::endl;
	else
		std::cout << "\x1b[31mfailure\x1b[0m" << std::endl;
}

/* unit test */

auto unit_tests_is_array(void) -> int {

	// avoid namespace pollution
	using namespace xns;

	test<true >(is_array<int[]>,          "int[]");
	test<true >(is_array<int[5]>,         "int[5]");
	test<false>(is_array<int(*)[5]>,      "int(*)[5]");
	test<false>(is_array<int(&)[5]>,      "int(&)[5]");
	test<false>(is_array<int(*)[]>,       "int(*)[]");
	test<false>(is_array<int>,            "int");
	test<false>(is_array<int&>,           "int&");
	test<false>(is_array<int*>,           "int*");
	test<true >(is_array<const int[]>,    "const int[]");
	test<true >(is_array<volatile int[]>, "volatile int[]");
	test<true >(is_array<const volatile int[]>, "const volatile int[]");

	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_ARRAY)
int main(void) {
	return unit_tests_is_array();
}
#endif






