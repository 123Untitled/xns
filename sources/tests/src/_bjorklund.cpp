#include "unit_tests.hpp"
#include "bjorklund.hpp"

#include "midi.hpp"
#include "benchmark.hpp"
#include "random.hpp"

/* unit test */

auto unit_tests_bjorklund(void) -> int {
	return 0;
}



#if defined(XNS_TEST_BJORKLUND)
int main(int argc, char** argv) {
	return unit_tests_bjorklund();
}
#endif

