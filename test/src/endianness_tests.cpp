#include "unit_tests.hpp"
#include "endianness.hpp"

/* unit test */
template <>
bool UT::unit_tests<"endianness">(void) {
	// code here...
	return false;
}

int main(void) {
	return UT::unit_tests<"endianness">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

