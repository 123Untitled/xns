#include "unit_tests.hpp"
#include "integral_constant.hpp"

/* unit test */
template <>
int UT::unit_tests<"integral_constant">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_INTEGRAL_CONSTANT)
int main(void) {
	return UT::unit_tests<"integral_constant">();
}
#endif


