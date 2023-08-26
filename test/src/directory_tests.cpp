#include "unit_tests.hpp"
#include "directory.hpp"

/* unit test */
template <>
bool UT::unit_tests<"directory">(void) {



	xns::filesystem::recursive_iterator it{"./inc"};

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
	return false;
}

int main(void) {

	UT::unit_tests<"directory">();

	return 0;
}
