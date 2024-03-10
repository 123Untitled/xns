#include "unit_tests.hpp"
#include "mutex.hpp"

/* unit test */
int unit_tests_mutex(void) {
	return 0;
}

#if defined(XNS_TEST_MUTEX)
int main(void) {
	return unit_tests_mutex();
}
#endif

