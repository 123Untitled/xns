#include "unit_tests.hpp"
#include "map.hpp"

#include "variant.hpp"
#include "random.hpp"
#include <chrono>
#include <map>
#include <set>



template <>
int UT::unit_tests<"map">(void) {
	return 0;
}


#if defined(XNS_TEST_MAP)
int main(void) {
	return UT::unit_tests<"map">();
}
#endif

