#include "unit_tests.hpp"
#include "is_scalar.hpp"

/* unit test */
template <>
int UT::unit_tests<"is_scalar">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_SCALAR)
int main(void) {
	return UT::unit_tests<"is_scalar">();
}
#endif


