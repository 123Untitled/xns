#include "unit_tests.hpp"
#include "is_arithmetic.hpp"

/* unit test */
template <>
int UT::unit_tests<"is_arithmetic">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_ARITHMETIC)
int main(void) {
	return UT::unit_tests<"is_arithmetic">();
}
#endif


