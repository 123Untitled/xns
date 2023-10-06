#include "unit_tests.hpp"
#include "is_fundamental.hpp"

/* unit test */
template <>
int UT::unit_tests<"is_fundamental">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_FUNDAMENTAL)
int main(void) {
	return UT::unit_tests<"is_fundamental">();
}
#endif


