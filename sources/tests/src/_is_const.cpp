#include "unit_tests.hpp"
#include "is_const.hpp"

/* unit test */
template <>
int UT::unit_tests<"is_const">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_CONST)
int main(void) {
	return UT::unit_tests<"is_const">();
}
#endif


