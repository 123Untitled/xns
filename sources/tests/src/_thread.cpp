#include "unit_tests.hpp"
#include "thread.hpp"
#include <thread>
#include "reference_wrapper.hpp"
#include "apply.hpp"

class A {

	public:
		A(void) {
		}
		A(const A&) {
			std::cout << "copy" << std::endl;
		}
		A(A&&) {
			std::cout << "move" << std::endl;
		}
		void print(void) const {
			std::cout << "Hello, World!" << std::endl;
		}

		void inc(void) {
			++toto;
		}
		int toto;
};

void printer(const A& a, int i) {
	//sleep(2);
	a.print();
	std::cout << i << std::endl;
}

/* unit test */
#include "invoke.hpp"

auto unit_tests_thread(void) -> int {
	/*
	const xns::tuple<A, int> t{A{}, 123};
	xns::apply(printer, t);
	*/

	{
		const A a;

		std::function<void(const A&)> f0 = &A::print;

		xns::invoke(f0, a);
	}

	return 0;


	A a0;

	xns::invoke(&A::print, a0);

	return 0;


	void(&f)(const A&, int) = printer;

	A a;
	auto ref = xns::ref(a);
	xns::invoke(&A::print, ref);

	xns::thread t0{&A::print, xns::ref(a)};




	std::cout << "joinable: " << t0.joinable() << std::endl;
	t0.join();
	std::cout << "joinable: " << t0.joinable() << std::endl;

	return 0;
}


#if defined(XNS_TEST_THREAD)
int main(void) {
	return unit_tests_thread();
}
#endif

