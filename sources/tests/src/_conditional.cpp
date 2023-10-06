#include "unit_tests.hpp"
#include "conditional.hpp"

/* unit test */
template <>
int UT::unit_tests<"conditional">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_CONDITIONAL)
int main(void) {
	return UT::unit_tests<"conditional">();
}
#endif


