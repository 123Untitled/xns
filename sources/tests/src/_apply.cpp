#include "unit_tests.hpp"
#include "apply.hpp"

/* unit test */
template <>
int UT::unit_tests<"apply">(void) {
	return 0;
}

#if defined(XNS_TEST_APPLY)
int main(void) {
	return UT::unit_tests<"apply">();
}
#endif

