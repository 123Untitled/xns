#include "unit_tests.hpp"
#include "thread.hpp"
#include <thread>
#include "apply.hpp"

class A {

	public:
		A(void) = default;
		void print(void) const {
			std::cout << "Hello, World!" << std::endl;
		}
};

void printer(const A& a, int i) {
	a.print();
	std::cout << i << std::endl;
}

/* unit test */
template <>
int UT::unit_tests<"thread">(void) {
	/*
	const xns::tuple<A, int> t{A{}, 123};
	xns::apply(printer, t);
	*/

	void(&f)(const A&, int) = printer;

	const A a;
	xns::thread t0{f, a, 123};

	t0.join();

	return 0;
}


#if defined(XNS_TEST_THREAD)
int main(void) {
	return UT::unit_tests<"thread">();
}
#endif

