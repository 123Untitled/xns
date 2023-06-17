#include "unit_tests.hpp"

void UT::environment_ut(void) {

	//xns::env::print();
	auto p = xns::env::get("PATH");

	if (p) {
		std::cout << *p << std::endl;
	}
	else {
		std::cout << "\"PATH\" not found" << std::endl;
	}

}
