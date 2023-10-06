#include "unit_tests.hpp"
#include "print.hpp"

/* unit test */
template <>
int UT::unit_tests<"print">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_PRINT)
int main(void) {
	return UT::unit_tests<"print">();
}
#endif


