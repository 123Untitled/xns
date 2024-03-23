#include "unit_tests.hpp"
#include "xns/type_traits/type_categories/is_member_pointer.hpp"

/* unit test */

auto unit_tests_is_member_pointer(void) -> int {
	// code here...
	return 0;
}

#if defined(XNS_TEST_IS_MEMBER_POINTER)
int main(void) {
	return unit_tests_is_member_pointer();
}
#endif


