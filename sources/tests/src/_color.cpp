#include "unit_tests.hpp"
#include "color/color.hpp"

/* unit test */

auto unit_tests_color(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_COLOR)
int main(void) {
	return unit_tests_color();
}
#endif

