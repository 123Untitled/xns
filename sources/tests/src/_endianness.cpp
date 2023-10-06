#include "unit_tests.hpp"
#include "endianness.hpp"

/* unit test */
template <>
int UT::unit_tests<"endianness">(void) {

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
	return UT::unit_tests<"endianness">();
}
#endif

