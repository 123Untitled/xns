#include "unit_tests.hpp"
#include "common_type.hpp"

/* unit test */

auto unit_tests_common_type(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_COMMON_TYPE)
int main(void) {
	return unit_tests_common_type();
}
#endif

