#include "unit_tests.hpp"
#include "type_traits/sequences/char_sequence.hpp"

/* unit test */

auto unit_tests_char_sequence(void) -> int {


	using seq = xns::make_character_sequence<"hello">;

	// code here...
	return 0;
}

#if defined(XNS_TEST_CHAR_SEQUENCE)
int main(void) {
	return unit_tests_char_sequence();
}
#endif


