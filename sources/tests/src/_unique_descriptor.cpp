#include "unit_tests.hpp"
#include "system/unique_descriptor.hpp"

/* unit test */
auto unit_tests_unique_descriptor(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_UNIQUE_DESCRIPTOR)
int main(void) {

	return unit_tests_unique_descriptor();
}
#endif


