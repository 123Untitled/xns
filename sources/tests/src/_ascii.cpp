#include "unit_tests.hpp"
#include "other/ascii.hpp"

/* unit test */

auto unit_tests_ascii(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_ASCII)
int main(void) {
	return unit_tests_ascii();
}
#endif

