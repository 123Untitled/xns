#include "unit_tests.hpp"
#include <iostream>
#include <iomanip>
#include "inheritance.hpp"

// avoid namespace pollution
using namespace xns;

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

namespace tests {

	class base {
		public:
			virtual ~base(void) = default;
	};

	class derived : public base {
		public:
			virtual ~derived(void) = default;
	};

}

/* unit test */

auto unit_tests_inheritance(void) -> int {


	tests::base base;

	tests::derived derived;

	test<true >(is_derived_from<tests::derived, tests::base>, "derived -> base");
	test<false>(is_derived_from<tests::base,    tests::derived>, "base -> derived");
	test<true>(is_derived_from<tests::base,    tests::base>, "base -> base");
	test<true>(is_derived_from<tests::derived, tests::derived>, "derived -> derived");

	// std version

	test<true >(std::derived_from<tests::derived, tests::base>, "derived -> base");
	test<false>(std::derived_from<tests::base,    tests::derived>, "base -> derived");
	test<true>(std::derived_from<tests::base,    tests::base>, "base -> base");
	test<true>(std::derived_from<tests::derived, tests::derived>, "derived -> derived");



	test<true >(is_base_of<tests::base,    tests::derived>, "base -> derived");
	test<false>(is_base_of<tests::derived, tests::base>, "derived -> base");
	test<true >(is_base_of<tests::base,    tests::base>, "base -> base");
	test<true >(is_base_of<tests::derived, tests::derived>, "derived -> derived");

	// std version

	test<true >(std::is_base_of_v<tests::base,    tests::derived>, "base -> derived");
	test<false>(std::is_base_of_v<tests::derived, tests::base>, "derived -> base");
	test<true >(std::is_base_of_v<tests::base,    tests::base>, "base -> base");
	test<true >(std::is_base_of_v<tests::derived, tests::derived>, "derived -> derived");

	// code here...
	return 0;
}

#if defined(XNS_TEST_INHERITANCE)
int main(void) {
	return unit_tests_inheritance();
}
#endif

