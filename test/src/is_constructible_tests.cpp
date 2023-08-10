#include "unit_tests.hpp"
#include "is_constructible.hpp"

/* unit test */
template <>
bool UT::unit_tests<"is_constructible">(void) {
	// code here...
	return false;
}

int main(void) {
	return UT::unit_tests<"is_constructible">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

