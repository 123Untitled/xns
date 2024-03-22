#include "unit_tests.hpp"
#include "type_traits/type_properties/is_unsigned.hpp"

/* unit test */

auto unit_tests_is_unsigned(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_UNSIGNED)
int main(void) {
	return unit_tests_is_unsigned();
}
#endif


