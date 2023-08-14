#include "unit_tests.hpp"
#include "directory.hpp"

/* unit test */
template <>
bool UT::unit_tests<"directory">(void) {



	xns::filesystem::recursive_iterator it{"./inc"};
	//xns::filesystem::iterator it{"."};
	int i = 0;

	while (it != nullptr) {

		auto view = it.name();
		auto path = it.path();

		//write(1, view.data(), view.size());
		//write(1, "\n", 1);
		write(1, path.data(), path.size());
		write(1, "\n", 1);
		//if (i > 10) break;
		//++i;
		++it;
	}

	// code here...
	return false;
}

int main(void) {

	UT::unit_tests<"directory">();

	return 0;
}
