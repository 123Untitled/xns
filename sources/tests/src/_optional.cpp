#include "unit_tests.hpp"
#include "xns/containers/optional.hpp"

#include <string>
#include <iostream>



void f(std::string& str) {
	std::cout << str << std::endl;
}


/* unit test */

auto unit_tests_optional(void) -> int {

	xns::optional<std::string> opt{};

	//f(opt);

	return 0;
}

#if defined(XNS_TEST_OPTIONAL)
int main(void) {
	return unit_tests_optional();
}
#endif


