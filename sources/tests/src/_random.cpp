#include "unit_tests.hpp"
#include "random.hpp"


template <>
bool UT::unit_tests<"random">(void) {


	using type = char;

	for (int i = 0; i < 1000; ++i) {
		type x = xns::random::integral<type>();
		std::cout << (int)x << " ";
	}
	std::cout << std::endl;

	return true;
}

int main(void) {
	UT::unit_tests<"random">();
	return 0;
}

