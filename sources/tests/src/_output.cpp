#include "unit_tests.hpp"
#include "terminal/output.hpp"

/* unit test */

auto unit_tests_output(void) -> int {

	xns::string str{ "Hello, world!" };

	xns::out::write(str);

	//xns::out::newline();
	xns::out::render();


	// code here...
	return 0;
}

#if defined(XNS_TEST_OUTPUT)
int main(void) {
	return unit_tests_output();
}
#endif

