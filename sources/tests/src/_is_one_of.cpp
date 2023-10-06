#include "unit_tests.hpp"
#include "is_one_of.hpp"

/* unit test */
template <>
int UT::unit_tests<"is_one_of">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_ONE_OF)
int main(void) {
	return UT::unit_tests<"is_one_of">();
}
#endif

