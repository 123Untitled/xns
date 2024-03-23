#include "unit_tests.hpp"
#include "xns/type_traits/type_operations/declval.hpp"

/* unit test */

auto unit_tests_declval(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_DECLVAL)
int main(void) {
	return unit_tests_declval();
}
#endif

