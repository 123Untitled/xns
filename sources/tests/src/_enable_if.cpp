#include "unit_tests.hpp"
#include "enable_if.hpp"

/* unit test */
template <>
int UT::unit_tests<"enable_if">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_ENABLE_IF)
int main(void) {
	return UT::unit_tests<"enable_if">();
}
#endif


