#include "unit_tests.hpp"
#include "char_sequence.hpp"

/* unit test */
template <>
int UT::unit_tests<"char_sequence">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_CHAR_SEQUENCE)
int main(void) {
	return UT::unit_tests<"char_sequence">();
}
#endif


