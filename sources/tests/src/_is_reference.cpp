#include "unit_tests.hpp"
#include "is_reference.hpp"

/* unit test */
template <>
int UT::unit_tests<"is_reference">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_REFERENCE)
int main(void) {
	return UT::unit_tests<"is_reference">();
}
#endif


