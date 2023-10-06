#include "unit_tests.hpp"
#include "escape.hpp"

/* unit test */
template <>
int UT::unit_tests<"escape">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_ESCAPE)
int main(void) {
	return UT::unit_tests<"escape">();
}
#endif


