#include "unit_tests.hpp"
#include "terminal.hpp"

/* unit test */
template <>
int UT::unit_tests<"terminal">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_TERMINAL)
int main(void) {
	return UT::unit_tests<"terminal">();
}
#endif


