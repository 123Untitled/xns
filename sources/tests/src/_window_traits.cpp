#include "unit_tests.hpp"

/* unit test */
template <>
int UT::unit_tests<"window_traits">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_WINDOW_TRAITS)
int main(void) {
	return UT::unit_tests<"window_traits">();
}
#endif


