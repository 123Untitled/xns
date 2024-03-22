#include "unit_tests.hpp"
#include "other/base.hpp"

/* unit test */

auto unit_tests_base(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_BASE)
int main(void) {
	return unit_tests_base();
}
#endif

