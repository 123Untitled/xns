#include "unit_tests.hpp"
#include "fixed.hpp"

/* unit test */
template <>
int UT::unit_tests<"fixed">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_FIXED)
int main(void) {
	return UT::unit_tests<"fixed">();
}
#endif

