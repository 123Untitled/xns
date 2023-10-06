#include "unit_tests.hpp"
#include "is_char.hpp"

/* unit test */
template <>
int UT::unit_tests<"is_char">(void) {
	// code here...
	return false;
}

#if defined(XNS_TEST_IS_CHAR)
int main(void) {
	return UT::unit_tests<"is_char">();
}
#endif


