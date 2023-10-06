#include "unit_tests.hpp"
#include "exceptions.hpp"

/* unit test */
template <>
int UT::unit_tests<"exceptions">(void) {
	// code here...
	return 0;
}


#if defined(XNS_TEST_EXCEPTIONS)
int main(void) {
	return UT::unit_tests<"exceptions">();
}
#endif

