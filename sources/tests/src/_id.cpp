#include "unit_tests.hpp"
#include "id.hpp"

/* unit test */
template <>
int UT::unit_tests<"id">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_ID)
int main(void) {
	return UT::unit_tests<"id">();
}
#endif
