#include "unit_tests.hpp"
#include "unique_descriptor.hpp"

/* unit test */
template <>
int UT::unit_tests<"unique_descriptor">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_UNIQUE_DESCRIPTOR)
int main(void) {
	return UT::unit_tests<"unique_descriptor">();
}
#endif


