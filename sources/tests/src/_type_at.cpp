#include "unit_tests.hpp"
#include "type_at.hpp"

/* unit test */
template <>
int UT::unit_tests<"type_at">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_TYPE_AT)
int main(void) {
	return UT::unit_tests<"type_at">();
}
#endif

