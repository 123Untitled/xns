#include "function.hpp"
#include <iostream>


void test(const char* msg, int n) {
	std::cout << msg << " " << n << std::endl;
}

/* unit test */
auto unit_tests_function(void) -> int {

	xns::function f1 = test;
	xns::function f2;
	xns::function f3 = f1;

	f1.call("f1", 42);

	xns::function<void(int)> f4;

	f4(42);

	return 0;
}

#if defined(XNS_TEST_FUNCTION)
int main(void) {
	return unit_tests_function();
}
#endif

