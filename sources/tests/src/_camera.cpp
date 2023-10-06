#include "unit_tests.hpp"
#include "camera.hpp"

/* unit test */
template <>
int UT::unit_tests<"camera">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_ADD_CONST)
int main(void) {
	return UT::unit_tests<"camera">();
}
#endif


