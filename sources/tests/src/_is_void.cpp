#include "unit_tests.hpp"
#include "is_void.hpp"

/* unit test */
template <>
int UT::unit_tests<"is_void">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_VOID)
int main(void) {
	return UT::unit_tests<"is_void">();
}
#endif


