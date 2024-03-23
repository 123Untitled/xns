#include "unit_tests.hpp"
#include "xns/type_traits/type_categories/is_char.hpp"

/* unit test */

auto unit_tests_is_char(void) -> int {
	// code here...
	return false;
}

#if defined(XNS_TEST_IS_CHAR)
int main(void) {
	return unit_tests_is_char();
}
#endif


