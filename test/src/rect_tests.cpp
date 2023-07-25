#include "unit_tests.hpp"
#include "rect.hpp"

/* unit test */
template <>
bool UT::unit_tests<"rect">(void) {

	xns::rect<int> r1(0, 0, 10, 10);

	xns::rect<float> r2(0.0f, 0.0f, 10.0f, 10.0f);

	// r1 = r2;

	// code here...
	return false;
}

