#include "unit_tests.hpp"
#include "time.hpp"

/* unit test */
template <>
bool UT::unit_tests<"time">(void) {
	int i = 0;

	while (i < 10000000) {
		auto t = xns::time::now();

		// print to ms
		std::cout << "time: " << t / 1000000 << "ms" << std::endl;
		++i;
	}

	// code here...
	return false;
}

int main(void) {
	UT::unit_tests<"time">();
	return 0;
}
