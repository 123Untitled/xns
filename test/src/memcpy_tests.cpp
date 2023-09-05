#include "unit_tests.hpp"
#include "memcpy.hpp"

/* unit test */
template <>
bool UT::unit_tests<"memcpy">(void) {
	// code here...
	return false;
}

int main(void) {
	return UT::unit_tests<"memcpy">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

