#include "unit_tests.hpp"
#include "aligned_storage.hpp"

/* unit test */
template <>
bool UT::unit_tests<"aligned_storage">(void) {
	// code here...
	return false;
}

int main(void) {
	return UT::unit_tests<"aligned_storage">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

