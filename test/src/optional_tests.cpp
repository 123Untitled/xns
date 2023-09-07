#include "unit_tests.hpp"
#include "optional.hpp"

/* unit test */
template <>
bool UT::unit_tests<"optional">(void) {
	// code here...
	return false;
}

int main(void) {
	return UT::unit_tests<"optional">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

