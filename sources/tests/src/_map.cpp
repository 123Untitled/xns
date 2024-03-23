#include "unit_tests.hpp"
#include "xns/containers/map.hpp"


auto unit_tests_map(void) -> int {
	return 0;
}


#if defined(XNS_TEST_MAP)
int main(void) {
	return unit_tests_map();
}
#endif

