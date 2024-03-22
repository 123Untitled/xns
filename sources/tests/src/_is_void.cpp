#include "unit_tests.hpp"
#include "type_traits/type_categories/is_void.hpp"

/* unit test */

auto unit_tests_is_void(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_VOID)
int main(void) {
	return unit_tests_is_void();
}
#endif


