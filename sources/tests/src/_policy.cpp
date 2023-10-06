#include "unit_tests.hpp"
#include "policy.hpp"

/* unit test */
template <>
int UT::unit_tests<"policy">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_POLICY)
int main(void) {
	return UT::unit_tests<"policy">();
}
#endif


