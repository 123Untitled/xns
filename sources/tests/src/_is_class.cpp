#include "unit_tests.hpp"
#include "is_class.hpp"

/* unit test */
template <>
int UT::unit_tests<"is_class">(void) {
	return 0;
}

#if defined(XNS_TEST_IS_CLASS)
int main(void) {
	return UT::unit_tests<"is_class">();
}
#endif

