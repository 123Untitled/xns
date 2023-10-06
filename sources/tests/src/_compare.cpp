#include "unit_tests.hpp"
#include "compare.hpp"

/* unit test */
template <>
int UT::unit_tests<"compare">(void) {
	// code here...
	return false;
}

#if defined(XNS_TEST_COMPARE)
int main(void) {
	return UT::unit_tests<"compare">();
}
#endif


