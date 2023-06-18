#include "unit_tests.hpp"
#include "environment.hpp"

template <>
bool UT::unit_tests<"environment">(void) {


	//xns::env::print();
	auto p = xns::env::get("PATH");

	if (p) {
		std::cout << *p << std::endl;
	}
	else {
		std::cout << "\"PATH\" not found" << std::endl;
	}


	return true;
}
