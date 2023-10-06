#include "unit_tests.hpp"
#include "color.hpp"

/* unit test */
template <>
int UT::unit_tests<"color">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_COLOR)
int main(void) {
	return UT::unit_tests<"color">();
}
#endif

