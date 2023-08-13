#include "unit_tests.hpp"
#include "poller.hpp"

/* unit test */
template <>
bool UT::unit_tests<"poller">(void) {
	// code here...
	return false;
}

int main(void) {
	return UT::unit_tests<"poller">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

