#include "unit_tests.hpp"
#include "rect.hpp"

/* unit test */

auto unit_tests_rect(void) -> int {

	xns::rect<int> r1(0, 0, 100, 100);

	PRECT(r1);

	auto rects = xns::horizontal_split<3>(r1);

	for (xns::size_t i = 0; i < rects.size(); ++i) {
		PRECT(rects[i]);
	}

	//xns::rect<float> r2(0, 0.0f, 10.0f, 10.0f);

	// code here...
	return 0;
}

#if defined(XNS_TEST_RECT)
int main(void) {
	return unit_tests_rect();
}
#endif

