#include "unit_tests.hpp"
#include "is_same.hpp"

/* unit test */
template <>
int UT::unit_tests<"is_same">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_SAME)
int main(void) {
	return UT::unit_tests<"is_same">();
}
#endif


