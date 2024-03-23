#include "unit_tests.hpp"
#include "xns/type_traits/type_categories/is_scalar.hpp"

/* unit test */

auto unit_tests_is_scalar(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_SCALAR)
int main(void) {
	return unit_tests_is_scalar();
}
#endif


