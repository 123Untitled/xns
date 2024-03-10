#include "thread.hpp"
#include "reference_wrapper.hpp"

class A {

	public:
		A(void)
		: toto{0} {
		}
		A(const A& other)
		: toto{other.toto} {
			std::cout << "copy" << std::endl;
		}

		A(A&& other) noexcept
		: toto{other.toto} {
			std::cout << "move" << std::endl;
		}

		void print(void) const {
			std::cout << "Hello, World!" << std::endl;
		}

		~A(void) {
			std::cout << "destroy" << std::endl;
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


auto unit_tests_thread(void) -> int {

	A a{};

	xns::thread t0{&A::print, a};
	//xns::thread t0{&A::print, xns::ref(a)};




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

