#include "unit_tests.hpp"
#include "integer_sequence.hpp"

/* unit test */
template <>
int UT::unit_tests<"integer_sequence">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_INTEGER_SEQUENCE)
int main(void) {
	return UT::unit_tests<"integer_sequence">();
}
#endif


