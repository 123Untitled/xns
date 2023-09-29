#include "unit_tests.hpp"
#include "thread.hpp"

/* unit test */
template <>
bool UT::unit_tests<"thread">(void) {
	// code here...
	return false;
}


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

int main(void) {

	/*
	const xns::tuple<A, int> t{A{}, 123};
	xns::apply(printer, t);
	*/

	void(&f)(const A&, int) = printer;

	const A a;
	xns::thread t0{f, a, 123};

	t0.join();

	return EXIT_SUCCESS;



	return UT::unit_tests<"thread">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

