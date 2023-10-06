#include "unit_tests.hpp"
#include "base.hpp"

/* unit test */
template <>
int UT::unit_tests<"base">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_BASE)
int main(void) {
	return UT::unit_tests<"base">();
}
#endif

