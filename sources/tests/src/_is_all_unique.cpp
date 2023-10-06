#include "unit_tests.hpp"
#include "is_all_unique.hpp"

/* unit test */
template <>
int UT::unit_tests<"is_all_unique">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_ALL_UNIQUE)
int main(void) {
	return UT::unit_tests<"is_all_unique">();
}
#endif


