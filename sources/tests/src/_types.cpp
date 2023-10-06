#include "unit_tests.hpp"
#include "types.hpp"

/* unit test */
template <>
int UT::unit_tests<"types">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_TYPES)
int main(void) {
	return UT::unit_tests<"types">();
}
#endif


