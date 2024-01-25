#include "unit_tests.hpp"
#include "random.hpp"



auto unit_tests_random(void) -> int {


	using type = char;

	for (int i = 0; i < 1000; ++i) {
		type x = xns::random::integral<type>();
		std::cout << (int)x << " ";
	}
	std::cout << std::endl;

	return 0;
}

#if defined(XNS_TEST_RANDOM)
int main(void) {
	return unit_tests_random();
}
#endif


