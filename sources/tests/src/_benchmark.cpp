#include "unit_tests.hpp"
#include "benchmark.hpp"

/* unit test */
template <>
int UT::unit_tests<"benchmark">(void) {
	return 0;
}

#if defined(XNS_TEST_BENCHMARK)
int main(void) {
	return UT::unit_tests<"benchmark">();
}
#endif

