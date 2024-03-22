#include "unit_tests.hpp"
#include "type_traits/type_categories/is_fundamental.hpp"

/* unit test */

auto unit_tests_is_fundamental(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_FUNDAMENTAL)
int main(void) {
	return unit_tests_is_fundamental();
}
#endif


