#include "unit_tests.hpp"
#include "add_const.hpp"

/* unit test */
template <>
int UT::unit_tests<"add_const">(void) {
	return 0;
}


#if defined(XNS_TEST_ADD_CONST)
int main(void) {
	return UT::unit_tests<"add_const">();
}
#endif
