#include "unit_tests.hpp"
#include "is_const.hpp"

/* unit test */

auto unit_tests_is_const(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_CONST)
int main(void) {
	return unit_tests_is_const();
}
#endif


