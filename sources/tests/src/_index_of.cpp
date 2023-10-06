#include "unit_tests.hpp"
#include "index_of.hpp"

/* unit test */
template <>
int UT::unit_tests<"index_of">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_INDEX_OF)
int main(void) {
	return UT::unit_tests<"index_of">();
}
#endif

