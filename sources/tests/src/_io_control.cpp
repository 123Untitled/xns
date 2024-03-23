#include "unit_tests.hpp"
#include "xns/terminal/io_control.hpp"

/* unit test */

auto unit_tests_io_control(void) -> int {
	return 0;
}

#if defined(XNS_TEST_IO_CONTROL)
int main(void) {
	return unit_tests_io_control();
}
#endif

