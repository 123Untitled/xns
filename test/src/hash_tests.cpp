#include "unit_tests.hpp"
#include "hash.hpp"

/* unit test */
template <>
bool UT::unit_tests<"hash">(void) {
	// code here...
	return false;
}

int main(void) {
	return UT::unit_tests<"hash">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

