#include "unit_tests.hpp"
#include "conditional.hpp"

/* unit test */

auto unit_tests_conditional(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_CONDITIONAL)
int main(void) {
	return unit_tests_conditional();
}
#endif


