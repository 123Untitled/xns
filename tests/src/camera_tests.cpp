#include "unit_tests.hpp"
#include "camera.hpp"

/* unit test */
template <>
bool UT::unit_tests<"camera">(void) {
	// code here...
	return false;
}

int main(void) {

	return UT::unit_tests<"camera">() ? EXIT_SUCCESS : EXIT_FAILURE;
}
