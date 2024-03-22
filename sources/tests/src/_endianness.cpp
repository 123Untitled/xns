#include "unit_tests.hpp"
#include "bit/endianness.hpp"

/* unit test */

auto unit_tests_endianness(void) -> int {

	if constexpr (xns::endianness::is_big()) {
		std::cout << "big endian" << std::endl;
	}
	else if constexpr (xns::endianness::is_little()) {
		std::cout << "little endian" << std::endl;
	}
	else {
		std::cout << "unknown endian" << std::endl;
	}
	return 0;
}

#if defined(XNS_TEST_ENDIANNESS)
int main(void) {
	return unit_tests_endianness();
}
#endif

