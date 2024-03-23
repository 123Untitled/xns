#include "unit_tests.hpp"
#include "xns/memory/weak_ptr.hpp"

/* unit test */

auto unit_tests_weak_ptr(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_WEAK_PTR)
int main(void) {
	return unit_tests_weak_ptr();
}
#endif


