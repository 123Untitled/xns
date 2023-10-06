#include "unit_tests.hpp"
#include "exec.hpp"

/* unit test */
template <>
int UT::unit_tests<"exec">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_EXEC)
int main(void) {
	return UT::unit_tests<"exec">();
}
#endif


