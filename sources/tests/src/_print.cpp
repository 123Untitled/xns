#include "unit_tests.hpp"
#include "print.hpp"

/* unit test */

auto unit_tests_print(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_PRINT)
int main(void) {
	return unit_tests_print();
}
#endif


