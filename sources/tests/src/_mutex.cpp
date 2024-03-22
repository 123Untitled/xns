#include "concurrency/mutex.hpp"
#include "concurrency/guard_lock.hpp"

/* unit test */
int unit_tests_mutex(void) {

	xns::mutex mutex;
	{
		xns::guard_lock lock{mutex};
	}

	return 0;
}

#if defined(XNS_TEST_MUTEX)
int main(void) {
	return unit_tests_mutex();
}
#endif

