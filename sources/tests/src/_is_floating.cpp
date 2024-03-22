#include "unit_tests.hpp"
#include "type_traits/type_categories/is_floating_point.hpp"

/* unit test */

auto unit_tests_is_floating(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_FLOATING)
int main(void) {
	return unit_tests_is_floating();
}
#endif


