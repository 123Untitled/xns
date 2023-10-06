#include "unit_tests.hpp"
#include "border.hpp"

/* unit test */
template <>
int UT::unit_tests<"border">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_BORDER)
int main(void) {
	return UT::unit_tests<"border">();
}
#endif



