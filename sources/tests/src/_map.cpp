#include "unit_tests.hpp"
#include "map.hpp"

#include "variant.hpp"
#include "random.hpp"
#include <chrono>
#include <map>
#include <set>




auto unit_tests_map(void) -> int {
	return 0;
}


#if defined(XNS_TEST_MAP)
int main(void) {
	return unit_tests_map();
}
#endif

