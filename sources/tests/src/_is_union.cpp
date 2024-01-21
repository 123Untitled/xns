#include "unit_tests.hpp"
#include "is_union.hpp"

/* unit test */
template <>
int UT::unit_tests<"is_union">(void) {
	return 0;
}

#if defined(XNS_TEST_IS_UNION)
int main(void) {
	return UT::unit_tests<"is_union">();
}
#endif

