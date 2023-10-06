#include "unit_tests.hpp"
#include "move.hpp"

/* unit test */
template <>
int UT::unit_tests<"move">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_MOVE)
int main(void) {
	return UT::unit_tests<"move">();
}
#endif


