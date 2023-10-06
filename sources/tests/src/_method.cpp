#include "unit_tests.hpp"
#include "method.hpp"

/* unit test */
template <>
int UT::unit_tests<"method">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_METHOD)
int main(void) {
	return UT::unit_tests<"method">();
}
#endif


