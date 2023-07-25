#include "unit_tests.hpp"
#include "random.hpp"


template <>
bool UT::unit_tests<"random">(void) {


	using type = double;

	for (int i = 0; i < 10; ++i) {
		std::cout << (type)xns::random::random_int<type>() << std::endl;
	}

	return true;
}

