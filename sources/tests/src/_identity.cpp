#include "unit_tests.hpp"
#include "xns/type_traits/other/identity.hpp"

/* unit test */

auto unit_tests_identity(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IDENTITY)
int main(void) {
	return unit_tests_identity();
}
#endif


