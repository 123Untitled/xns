#include "unit_tests.hpp"
#include "hash_set.hpp"

/* unit test */
template <>
bool UT::unit_tests<"hash_set">(void) {
	// code here...
	return false;
}

int main(void) {
	return UT::unit_tests<"hash_set">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

