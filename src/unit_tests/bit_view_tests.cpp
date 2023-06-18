#include "unit_tests.hpp"
#include "bit_view.hpp"

template <>
bool UT::unit_tests<"bit_view">(void) {


	char a = 123;

	xns::bit_view bs(a);

	bs.print();

	bs.set(0);



	return true;
}


