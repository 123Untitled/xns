#include "unit_tests.hpp"
#include "debug.hpp"

/* unit test */
template <>
int UT::unit_tests<"debug">(void) {

	xns::debug::print("Hello, world! %d\n", 42);
	// code here...
	return 0;
}

#if defined(XNS_TEST_DEBUG)
int main(void) {
	return UT::unit_tests<"debug">();
}
#endif


