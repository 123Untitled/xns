#include "unit_tests.hpp"
#include "output.hpp"

/* unit test */
template <>
int UT::unit_tests<"output">(void) {

	xns::string str{ "Hello, world!" };

	xns::out::write(str);

	//xns::out::newline();
	xns::out::render();


	// code here...
	return 0;
}

#if defined(XNS_TEST_OUTPUT)
int main(void) {
	return UT::unit_tests<"output">();
}
#endif

