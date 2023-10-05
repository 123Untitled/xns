#include "unit_tests.hpp"
#include "endianness.hpp"

/* unit test */
template <>
bool UT::unit_tests<"endianness">(void) {
	// code here...
	return false;
}

int main(void) {

	if constexpr (xns::endianness::is_big()) {
		std::cout << "big endian" << std::endl;
	}
	else if constexpr (xns::endianness::is_little()) {
		std::cout << "little endian" << std::endl;
	}
	else {
		std::cout << "unknown endian" << std::endl;
	}


	return UT::unit_tests<"endianness">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

