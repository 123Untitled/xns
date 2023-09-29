#include "unit_tests.hpp"
#include "debug.hpp"

/* unit test */
template <>
bool UT::unit_tests<"debug">(void) {

	xns::debug::print("Hello, world! %d\n", 42);
	// code here...
	return false;
}

