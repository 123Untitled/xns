#include "unit_tests.hpp"
#include "output.hpp"

/* unit test */
template <>
bool UT::unit_tests<"output">(void) {

	xns::string str{ "Hello, world!" };

	xns::out::write(str);

	//xns::out::newline();
	xns::out::render();


	// code here...
	return false;
}

int main(void) {

	UT::unit_tests<"output">();


	return 0;
}
