#include "unit_tests.hpp"
#include "is_null.hpp"

/* unit test */
template <>
int UT::unit_tests<"is_null">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_NULL)
int main(void) {
	return UT::unit_tests<"is_null">();
}
#endif


