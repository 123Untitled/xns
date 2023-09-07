#include "unit_tests.hpp"
#include "segment.hpp"

/* unit test */
template <>
bool UT::unit_tests<"segment">(void) {
	// code here...
	return false;
}

int main(void) {
	return UT::unit_tests<"segment">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

