#include "unit_tests.hpp"
#include "xns/type_traits/type_operations/forward.hpp"

/* unit test */

auto unit_tests_forward(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_FORWARD)
int main(void) {
	return unit_tests_forward();
}
#endif


