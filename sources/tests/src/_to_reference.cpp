#include "unit_tests.hpp"
#include "type_traits/other/to_reference.hpp"

/* unit test */

auto unit_tests_to_reference(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_TO_REFERENCE)
int main(void) {
	return unit_tests_to_reference();
}
#endif

