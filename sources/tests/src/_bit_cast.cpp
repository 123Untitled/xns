#include "unit_tests.hpp"
#include "bit_cast.hpp"

/* unit test */
template <>
int UT::unit_tests<"bit_cast">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_BIT_CAST)
int main(void) {
	return UT::unit_tests<"bit_cast">();
}
#endif


