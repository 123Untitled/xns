#include "unit_tests.hpp"
#include "bjorklund.hpp"

#include "midi.hpp"
#include "benchmark.hpp"
#include "random.hpp"

/* unit test */
template <>
int UT::unit_tests<"bjorklund">(void) {
	return 0;
}



#if defined(XNS_TEST_BJORKLUND)
int main(int argc, char** argv) {
	return UT::unit_tests<"bjorklund">();
}
#endif

