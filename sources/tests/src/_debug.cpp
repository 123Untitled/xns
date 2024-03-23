#include "unit_tests.hpp"
#include "xns/other/debug.hpp"

/* unit test */

auto unit_tests_debug(void) -> int {

	xns::debug::print("Hello, world! %d\n", 42);
	// code here...
	return 0;
}

#if defined(XNS_TEST_DEBUG)
int main(void) {
	return unit_tests_debug();
}
#endif


