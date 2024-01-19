#include "unit_tests.hpp"
#include "time.hpp"


static void func(void) {
	std::cout << "func" << std::endl;
}

/* unit test */
template <>
int UT::unit_tests<"time">(void) {

	xns::bpm tempo{120};

	xns::time::clock(func, tempo);

	int i = 0;

	xns::time::now();
	//return 0;
	while (i < 10000000) {
		auto t = xns::time::now();
		// print to ms
		std::cout << "time: " << t / 1000000 << "ms" << std::endl;
		++i;
	}

	return 0;
}

#if defined(XNS_TEST_TIME)
int main(void) {
	return UT::unit_tests<"time">();
}
#endif

