#include "unit_tests.hpp"
#include "types.hpp"
#include <string>

/* unit test */

auto unit_tests_types(void) -> int {

	std::cout << "bits in a char: " << xns::bits_per_byte << std::endl;
	std::cout << "bytes in a pointer: " << xns::bytes_per_address << std::endl;

	xns::_unsigned<4> _un;

	std::cout << "integer bytes: " << sizeof(_un) << std::endl;


	// code here...
	return 0;
}

#if defined(XNS_TEST_TYPES)
int main(void) {
	return unit_tests_types();
}
#endif


