#include "unit_tests.hpp"
#include "xns/type_traits/other/type_at.hpp"

/* unit test */

auto unit_tests_type_at(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_TYPE_AT)
int main(void) {
	return unit_tests_type_at();
}
#endif

