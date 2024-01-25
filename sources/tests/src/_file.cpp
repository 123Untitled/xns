#include "unit_tests.hpp"
#include "file.hpp"

/* unit test */

auto unit_tests_file(void) -> int {


	xns::file<2048> file{xns::string{"make.sh"}, O_RDWR | O_CREAT, 0644};

	while (file.read()) {

		xns::size_t i = 0;

		while (i < file.readed()) {
			std::cout << file[i];
			++i;
		}
	}


	// code here...
	return 0;
}

#if defined(XNS_TEST_FILE)
int main(void) {
	return unit_tests_file();
}
#endif

