#include "unit_tests.hpp"
#include "add_const.hpp"

/* unit test */

auto unit_tests_add_const(void) -> int {
	return 0;
}


#if defined(XNS_TEST_ADD_CONST)
int main(void) {
	return unit_tests_add_const();
}
#endif
