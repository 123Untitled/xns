#include "unit_tests.hpp"
#include "common_type.hpp"

/* unit test */
template <>
int UT::unit_tests<"common_type">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_COMMON_TYPE)
int main(void) {
	return UT::unit_tests<"common_type">();
}
#endif

