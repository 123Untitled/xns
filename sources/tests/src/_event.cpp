#include "unit_tests.hpp"
#include "event.hpp"

/* unit test */
template <>
int UT::unit_tests<"event">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_EVENT)
int main(void) {
	return UT::unit_tests<"event">();
}
#endif


