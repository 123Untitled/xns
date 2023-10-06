#include "unit_tests.hpp"
#include "environment.hpp"

template <>
int UT::unit_tests<"environment">(void) {

	//xns::env::print();
	auto p = xns::env::get("PATH");

	if (p) {
		std::cout << *p << std::endl;
	}
	else {
		std::cout << "\"PATH\" not found" << std::endl;
	}

	return 0;
}


#if defined(XNS_TEST_ENVIRONMENT)
int main(void) {
	return UT::unit_tests<"environment">();
}
#endif

