#include "unit_tests.hpp"
#include "io_control.hpp"

/* unit test */
template <>
int UT::unit_tests<"io_control">(void) {
	return 0;
}

#if defined(XNS_TEST_IO_CONTROL)
int main(void) {
	return UT::unit_tests<"io_control">();
}
#endif

