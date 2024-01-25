#include "unit_tests.hpp"
#include "exec.hpp"

/* unit test */

auto unit_tests_exec(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_EXEC)
int main(void) {
	return unit_tests_exec();
}
#endif


