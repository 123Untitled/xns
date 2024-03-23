#include "xns/invoke/method.hpp"
#include <iostream>


struct A {

	void print(void) {
		std::cout << "hello world" << std::endl;
	}
	
};

/* unit test */
auto unit_tests_method(void) -> int {

	xns::method<A, void(void)> m0{&A::print};
	xns::method m1{&A::print};

	A a;

	m0(a);
	m1(a);

	return 0;
}

#if defined(XNS_TEST_METHOD)
int main(void) {
	return unit_tests_method();
}
#endif


