#include "unit_tests.hpp"
#include "ascii.hpp"

/* unit test */
template <>
int UT::unit_tests<"ascii">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_ASCII)
int main(void) {
	return UT::unit_tests<"ascii">();
}
#endif

