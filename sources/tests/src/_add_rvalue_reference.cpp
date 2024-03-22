#include "unit_tests.hpp"
#include "type_traits/type_modifications/add_rvalue_reference.hpp"

/* unit test */
int unit_tests_add_rvalue_reference(void) {
	return 0;
}

#if defined(XNS_TEST_ADD_RVALUE_REFERENCE)
int main(void) {
	return unit_tests_add_rvalue_reference();
}
#endif

