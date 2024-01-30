#include "unit_tests.hpp"
#include "compressed_pair.hpp"

/* unit test */
template <>
int UT::unit_tests<"compressed_pair">(void) {
	return 0;
}

#if defined(XNS_TEST_COMPRESSED_PAIR)
int main(void) {
	return UT::unit_tests<"compressed_pair">();
}
#endif

