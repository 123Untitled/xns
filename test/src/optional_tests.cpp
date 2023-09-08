#include "unit_tests.hpp"
#include "optional.hpp"
#include "testclass.hpp"




void f(test::B& b) {
	std::cout << b << std::endl;
}


/* unit test */
template <>
bool UT::unit_tests<"optional">(void) {


	xns::optional<test::B> opt{};


	f(opt);





	return false;
}

int main(void) {
	return UT::unit_tests<"optional">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

