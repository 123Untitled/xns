#include "unit_tests.hpp"
#include "rect.hpp"

/* unit test */
template <>
bool UT::unit_tests<"rect">(void) {

	xns::rect<int> r1(0, 0, 100, 100);

	PRECT(r1);

	auto rects = xns::horizontal_split<3>(r1);

	for (xns::size_t i = 0; i < rects.size(); ++i) {
		PRECT(rects[i]);
	}



	//xns::rect<float> r2(0, 0.0f, 10.0f, 10.0f);


	// code here...
	return false;
}

int main(void) {


	int i = -1;
	int j = -1;

	std::cout << i + j << std::endl;


	UT::unit_tests<"rect">();

	return 0;
}
