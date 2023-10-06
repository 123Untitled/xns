#include "unit_tests.hpp"
#include "is_member_pointer.hpp"

/* unit test */
template <>
int UT::unit_tests<"is_member_pointer">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_MEMBER_POINTER)
int main(void) {
	return UT::unit_tests<"is_member_pointer">();
}
#endif


