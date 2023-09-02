#include "unit_tests.hpp"
#include "memory.hpp"

/* unit test */
template <>
bool UT::unit_tests<"memory">(void) {
	// code here...
	return false;
}

int main(void) {
	return UT::unit_tests<"memory">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

