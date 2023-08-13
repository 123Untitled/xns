#include "unit_tests.hpp"
#include "vector.hpp"

/* unit test */
template <>
bool UT::unit_tests<"vector">(void) {

	xns::vector<int> v;
	// code here...
	return false;
}

int main(void) {
	UT::unit_tests<"vector">();
	return 0;
}
