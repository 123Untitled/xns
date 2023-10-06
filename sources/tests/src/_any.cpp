#include "unit_tests.hpp"
#include "any.hpp"

/* unit test */
template <>
int UT::unit_tests<"any">(void) {
	// code here...
	return false;
}

#if defined(XNS_TEST_ANY)
int main(void) {
	return UT::unit_tests<"any">();
}
#endif

