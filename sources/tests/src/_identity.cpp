#include "unit_tests.hpp"
#include "identity.hpp"

/* unit test */
template <>
int UT::unit_tests<"identity">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IDENTITY)
int main(void) {
	return UT::unit_tests<"identity">();
}
#endif


