#include "unit_tests.hpp"
#include "xorshift.hpp"


template <>
int UT::unit_tests<"xorshift">(void) {
	return 0;
}

#if defined(XNS_TEST_XORSHIFT)
int main(void) {
	return UT::unit_tests<"xorshift">();
}
#endif


