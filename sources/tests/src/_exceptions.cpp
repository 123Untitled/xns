#include "unit_tests.hpp"
#include "diagnostics/exceptions.hpp"

/* unit test */

auto unit_tests_exceptions(void) -> int {
	// code here...
	return 0;
}


#if defined(XNS_TEST_EXCEPTIONS)
int main(void) {
	return unit_tests_exceptions();
}
#endif

