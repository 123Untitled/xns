#include "unit_tests.hpp"
#include "enable_if.hpp"

/* unit test */

auto unit_tests_enable_if(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_ENABLE_IF)
int main(void) {
	return unit_tests_enable_if();
}
#endif


