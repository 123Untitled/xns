#include "unit_tests.hpp"
#include "file.hpp"

/* unit test */
template <>
bool UT::unit_tests<"file">(void) {


	xns::file file{"test.txt", O_RDWR | O_CREAT, 0644};


	// code here...
	return false;
}

int main(void) {

	UT::unit_tests<"file">();

	return 0;
}
