#include "unit_tests.hpp"
#include "invoke/callable.hpp"

class toto {

	public:
		toto(void) = default;
		void print(int i) volatile & {
			std::cout << i << std::endl;
		}
		~toto(void) = default;
};

template <typename T>
class method_;

template <typename R, typename C, typename... A>
class method_<R(C::*)(A...)> {
	public:
		method_(void) = default;
};


/* unit test */

auto unit_tests_callable(void) -> int {

	toto t;
	using proto = void(toto::*)(int) volatile;
	//proto p = &toto::print;

	//method_<proto> m;



	//xns::callable<proto> c1{&toto::print, t};

	return 0;
}


#if defined(XNS_TEST_CALLABLE)
int main(void) {
	return unit_tests_callable();
}
#endif


