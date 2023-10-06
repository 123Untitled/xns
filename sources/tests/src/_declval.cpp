#include "unit_tests.hpp"
#include "declval.hpp"

/* unit test */
template <>
int UT::unit_tests<"declval">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_DECLVAL)
int main(void) {
	return UT::unit_tests<"declval">();
}
#endif

