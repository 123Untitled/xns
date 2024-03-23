#include "unit_tests.hpp"
#include "xns/system/directory.hpp"

/* unit test */

auto unit_tests_directory(void) -> int {

	xns::filesystem::recursive_iterator it{xns::string{"./inc"}};

	//xns::filesystem::iterator it{"."};
	int i = 0;

	while (it != nullptr) {

		if (it.is_directory()) {
			xns::print("\x1b[31mDIR\x1b[0m ", it.name(), '\n');
		}
		else if (it.is_regular()) {
			xns::print("\x1b[32mREG\x1b[0m ", it.name(), '\n');
		}
		++it;
	}
	xns::out::render();

	// code here...
	return 0;
}

#if defined(XNS_TEST_DIRECTORY)
int main(void) {
	return unit_tests_directory();
}
#endif

