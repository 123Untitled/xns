#include "unit_tests.hpp"
#include "policy.hpp"

/* unit test */

auto unit_tests_policy(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_POLICY)
int main(void) {
	return unit_tests_policy();
}
#endif


