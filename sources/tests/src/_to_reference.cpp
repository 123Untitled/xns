#include "unit_tests.hpp"
#include "to_reference.hpp"

/* unit test */
template <>
int UT::unit_tests<"to_reference">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_TO_REFERENCE)
int main(void) {
	return UT::unit_tests<"to_reference">();
}
#endif

