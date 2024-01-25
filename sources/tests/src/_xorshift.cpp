#include "unit_tests.hpp"
#include "xorshift.hpp"



auto unit_tests_xorshift(void) -> int {
	return 0;
}

#if defined(XNS_TEST_XORSHIFT)
int main(void) {
	return unit_tests_xorshift();
}
#endif


