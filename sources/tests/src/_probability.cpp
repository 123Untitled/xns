#include "unit_tests.hpp"
#include "probability.hpp"

/* unit test */
template <>
int UT::unit_tests<"probability">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_PROBABILITY)
int main(void) {
	return UT::unit_tests<"probability">();
}
#endif


