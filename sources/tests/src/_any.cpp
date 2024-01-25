#include "unit_tests.hpp"
#include "any.hpp"

/* unit test */

auto unit_tests_any(void) -> int {
	// code here...
	return false;
}

#if defined(XNS_TEST_ANY)
int main(void) {
	return unit_tests_any();
}
#endif

