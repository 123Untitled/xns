#include "unit_tests.hpp"
#include "file.hpp"

/* unit test */
template <>
int UT::unit_tests<"file">(void) {


	xns::file file{"test.txt", O_RDWR | O_CREAT, 0644};


	// code here...
	return 0;
}

#if defined(XNS_TEST_FILE)
int main(void) {
	return UT::unit_tests<"file">();
}
#endif

