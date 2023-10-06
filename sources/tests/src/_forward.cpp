#include "unit_tests.hpp"
#include "forward.hpp"

/* unit test */
template <>
int UT::unit_tests<"forward">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_FORWARD)
int main(void) {
	return UT::unit_tests<"forward">();
}
#endif


