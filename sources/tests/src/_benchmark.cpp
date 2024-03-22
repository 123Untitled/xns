#include "unit_tests.hpp"
#include "other/benchmark.hpp"

/* unit test */

auto unit_tests_benchmark(void) -> int {
	return 0;
}

#if defined(XNS_TEST_BENCHMARK)
int main(void) {
	return unit_tests_benchmark();
}
#endif

