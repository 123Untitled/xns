#include "unit_tests.hpp"
#include "weak_ptr.hpp"

/* unit test */
template <>
int UT::unit_tests<"weak_ptr">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_WEAK_PTR)
int main(void) {
	return UT::unit_tests<"weak_ptr">();
}
#endif


