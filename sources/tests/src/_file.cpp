#include "unit_tests.hpp"
#include "file.hpp"

/* unit test */
template <>
int UT::unit_tests<"file">(void) {


	xns::file<2048> file{"make.sh", O_RDWR | O_CREAT, 0644};

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
	return UT::unit_tests<"file">();
}
#endif

