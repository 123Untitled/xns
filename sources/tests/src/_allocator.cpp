#include "unit_tests.hpp"
#include "allocator.hpp"

/* unit test */
template <>
int UT::unit_tests<"allocator">(void) {
	// code here...
	return false;
}

#if defined(XNS_TEST_ALLOCATOR)
int main(void) {
	return UT::unit_tests<"allocator">();
}
#endif

