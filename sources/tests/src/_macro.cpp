#include "unit_tests.hpp"
#include "macros.hpp"

/* unit test */
template <>
int UT::unit_tests<"macros">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_MACROS)
int main(void) {
	return UT::unit_tests<"macros">();
}
#endif


