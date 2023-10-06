#include "unit_tests.hpp"
#include "parameter_pack.hpp"

/* unit test */
template <>
int UT::unit_tests<"parameter_pack">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_PARAMETER_PACK)
int main(void) {
	return UT::unit_tests<"parameter_pack">();
}
#endif

