#include "unit_tests.hpp"
#include "is_function.hpp"

/* unit test */
template <>
bool UT::unit_tests<"is_function">(void) {
	// code here...
	return false;
}

int main(void) {
	return UT::unit_tests<"is_function">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

