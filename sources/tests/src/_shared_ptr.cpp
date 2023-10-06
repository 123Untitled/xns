#include "unit_tests.hpp"
#include "shared_ptr.hpp"

/* unit test */
template <>
int UT::unit_tests<"shared_ptr">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_SHARED_PTR)
int main(void) {
	return UT::unit_tests<"shared_ptr">();
}
#endif


