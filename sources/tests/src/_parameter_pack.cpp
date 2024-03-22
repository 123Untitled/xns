#include "unit_tests.hpp"
#include "type_traits/other/parameter_pack.hpp"

/* unit test */

auto unit_tests_parameter_pack(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_PARAMETER_PACK)
int main(void) {
	return unit_tests_parameter_pack();
}
#endif

