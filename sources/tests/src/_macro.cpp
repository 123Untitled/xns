#include "unit_tests.hpp"
#include "macros.hpp"

/* unit test */

auto unit_tests_macros(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_MACROS)
int main(void) {
	return unit_tests_macros();
}
#endif


