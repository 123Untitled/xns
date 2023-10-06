#include "unit_tests.hpp"
#include "is_floating.hpp"

/* unit test */
template <>
int UT::unit_tests<"is_floating">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_FLOATING)
int main(void) {
	return UT::unit_tests<"is_floating">();
}
#endif


