#include "unit_tests.hpp"
#include "method.hpp"
#include "function.hpp"

#include "compressed_pair.hpp"

struct A {

	void print(void) const {
		std::cout << "hello world" << std::endl;
	}
	
};

class B {
	int i;
};

class C {
	A a;
	int i;
};


class D {
	public:
	D(void) = delete;
	D(int) { }
	D(const D&) = default;
};

class E {

	public:
	E(void) = delete;
	E(int) { }
	E(const E&) = default;
};


/* unit test */

auto unit_tests_method(void) -> int {

	xns::compressed_pair<D, E> p0{1, 2};

	std::__compressed_pair<D, E> p1{1, 2};

	std::cout << "sizeof compressed_pair<A, B>: " << sizeof(xns::compressed_pair<A, B>) << std::endl;
	std::cout << "sizeof compressed_pair<A, B>: " << sizeof(std::__compressed_pair<A, B>) << std::endl;
	std::cout << "sizeof(C): " << sizeof(C) << std::endl;


	std::cout << "is empty: " << __is_empty(B) << std::endl;


	xns::function<void(void)> f0{[]() {
		std::cout << "hello world" << std::endl;
	}};

	f0.call();

	A a0;

	std::cout << "sizeof(A): " << sizeof(A) << std::endl;
	std::cout << "sizeof(B): " << sizeof(B) << std::endl;

	//xns::method<A, void(void)> m0{&A::print};

	// code here...
	return 0;
}

#if defined(XNS_TEST_METHOD)
int main(void) {
	return unit_tests_method();
}
#endif


