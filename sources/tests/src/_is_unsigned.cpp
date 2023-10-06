#include "unit_tests.hpp"
#include "is_unsigned.hpp"

/* unit test */
template <>
int UT::unit_tests<"is_unsigned">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_UNSIGNED)
int main(void) {
	return UT::unit_tests<"is_unsigned">();
}
#endif


