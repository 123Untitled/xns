#include "unit_tests.hpp"
#include "method.hpp"

/* unit test */

auto unit_tests_method(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_METHOD)
int main(void) {
	return unit_tests_method();
}
#endif


