#include "unit_tests.hpp"
#include "xns/event/event.hpp"

/* unit test */

auto unit_tests_event(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_EVENT)
int main(void) {
	return unit_tests_event();
}
#endif


