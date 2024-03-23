#include "unit_tests.hpp"
#include "xns/random/id.hpp"

/* unit test */

auto unit_tests_id(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_ID)
int main(void) {
	return unit_tests_id();
}
#endif
