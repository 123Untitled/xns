#include "unit_tests.hpp"
#include "xns/type_traits/type_modifications/remove.hpp"

/* unit test */

auto unit_tests_remove(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_REMOVE)
int main(void) {
	return unit_tests_remove();
}
#endif


