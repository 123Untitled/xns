#include "unit_tests.hpp"
#include "callable.hpp"

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
template <>
bool UT::unit_tests<"callable">(void) {

	toto t;
	using proto = void(toto::*)(int) volatile;
	//proto p = &toto::print;

	//method_<proto> m;



	//xns::callable<proto> c1{&toto::print, t};

	return false;
}




int main(void) {

	UT::unit_tests<"callable">();

	return 0;
}
