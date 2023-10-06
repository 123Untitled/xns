#include "unit_tests.hpp"
#include "evntype.hpp"

/* unit test */
template <>
int UT::unit_tests<"evntype">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_EVNTYPE)
int main(void) {
	return UT::unit_tests<"evntype">();
}
#endif


