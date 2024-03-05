#include "unit_tests.hpp"
#include "static_vector.hpp"

/* unit test */
template <>
int UT::unit_tests<"static_vector">(void) {
	return 0;
}

#if defined(XNS_TEST_STATIC_VECTOR)
int main(void) {
	return UT::unit_tests<"static_vector">();
}
#endif

