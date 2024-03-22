#include "unit_tests.hpp"
#include "event/input.hpp"
#include "terminal/terminal.hpp"


auto unit_tests_input(void) -> int {


	xns::terminal::raw(xns::VFlag::NON_BLOCKING);

	auto str = xns::in::read();

	std::cout << "size: " << str.size() << std::endl;
	std::cout << "capacity: " << str.capacity() << std::endl;

	for (xns::size_t i = 0; i < str.size(); ++i) {

		if (str[i] == '\0') {
			std::cout << "c: \\0" << std::endl;
		}
		else if (str[i] < 32) {
			std::cout << "c: " << "? " << static_cast<int>(str[i]) << std::endl;
		} else {
			std::cout << "c: " << str[i] << " " << static_cast<int>(str[i]) << std::endl;
		}
	}

	xns::terminal::restore();

	return 0;
}

#if defined(XNS_TEST_INPUT)
int main(void) {
	return unit_tests_input();
}
#endif

