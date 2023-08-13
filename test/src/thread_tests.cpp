#include "unit_tests.hpp"
#include "thread.hpp"

/* unit test */
template <>
bool UT::unit_tests<"thread">(void) {
	// code here...
	return false;
}

int main(void) {
	return UT::unit_tests<"thread">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

