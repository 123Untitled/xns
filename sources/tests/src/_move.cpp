#include "unit_tests.hpp"
#include "type_traits/type_operations/move.hpp"
#include <string>

/* unit test */

auto unit_tests_move(void) -> int {


	std::string a{"hello"};

	std::string b{xns::move(a)};


	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;


	// code here...
	return 0;
}

#if defined(XNS_TEST_MOVE)
int main(void) {
	return unit_tests_move();
}
#endif


