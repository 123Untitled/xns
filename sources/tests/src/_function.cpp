#include "unit_tests.hpp"
#include "function.hpp"

/* unit test */
template <>
int UT::unit_tests<"function">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_FUNCTION)
int main(void) {
	return UT::unit_tests<"function">();
}
#endif

