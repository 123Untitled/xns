#include "unit_tests.hpp"
#include "allocator.hpp"

/* unit test */

auto unit_tests_allocator(void) -> int {
	// code here...
	return false;
}

#if defined(XNS_TEST_ALLOCATOR)
int main(void) {
	return unit_tests_allocator();
}
#endif

