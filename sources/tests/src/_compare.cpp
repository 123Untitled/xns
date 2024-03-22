#include "unit_tests.hpp"
#include "type_traits/other/compare.hpp"

/* unit test */

auto unit_tests_compare(void) -> int {
	// code here...
	return false;
}

#if defined(XNS_TEST_COMPARE)
int main(void) {
	return unit_tests_compare();
}
#endif


