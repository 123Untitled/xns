#include "unit_tests.hpp"
#include "move.hpp"
#include <string>

/* unit test */
template <>
int UT::unit_tests<"move">(void) {


	std::string a{"hello"};

	std::string b{xns::move(a)};


	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;


	// code here...
	return 0;
}

#if defined(XNS_TEST_MOVE)
int main(void) {
	return UT::unit_tests<"move">();
}
#endif


