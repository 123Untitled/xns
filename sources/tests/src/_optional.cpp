#include "unit_tests.hpp"
#include "optional.hpp"

#include <string>
#include <iostream>



void f(std::string& str) {
	std::cout << str << std::endl;
}


/* unit test */
template <>
int UT::unit_tests<"optional">(void) {

	xns::optional<std::string> opt{};

	//f(opt);

	return 0;
}

#if defined(XNS_TEST_OPTIONAL)
int main(void) {
	return UT::unit_tests<"optional">();
}
#endif


