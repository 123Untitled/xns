#include "unit_tests.hpp"
#include "type_traits/type_categories/is_null.hpp"

/* unit test */

auto unit_tests_is_null(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_NULL)
int main(void) {
	return unit_tests_is_null();
}
#endif


