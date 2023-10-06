#include "unit_tests.hpp"
#include "remove.hpp"

/* unit test */
template <>
int UT::unit_tests<"remove">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_REMOVE)
int main(void) {
	return UT::unit_tests<"remove">();
}
#endif


