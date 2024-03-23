#include "unit_tests.hpp"
#include "xns/type_traits/sequences/integer_sequence.hpp"

/* unit test */

auto unit_tests_integer_sequence(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_INTEGER_SEQUENCE)
int main(void) {
	return unit_tests_integer_sequence();
}
#endif


