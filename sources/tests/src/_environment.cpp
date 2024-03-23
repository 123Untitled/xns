#include "unit_tests.hpp"
#include "xns/terminal/environment.hpp"


auto unit_tests_environment(void) -> int {

	//xns::env::print();
	auto p = xns::env::get(xns::string{"PATH"});

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
	return unit_tests_environment();
}
#endif

