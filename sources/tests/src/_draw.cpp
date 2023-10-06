#include "unit_tests.hpp"
#include "draw.hpp"

/* unit test */
template <>
int UT::unit_tests<"draw">(void) {
	// code here...
	return false;
}

#if defined(XNS_TEST_DRAW)
int main(void) {
	return UT::unit_tests<"draw">();
}
#endif

