#include "unit_tests.hpp"
#include "bjorklund.hpp"

/* unit test */
template <>
int UT::unit_tests<"bjorklund">(void) {
	return 0;
}

#if defined(XNS_TEST_BJORKLUND)
int main(void) {
	return UT::unit_tests<"bjorklund">();
}
#endif

