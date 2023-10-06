#include "unit_tests.hpp"
#include "is_function.hpp"



class A {

	public:
		A(void) = default;
		void print(void) const {
			std::cout << "Hello, World!" << std::endl;
		}
};

void print_(const A& a) {
	a.print();
}


/* unit test */
template <>
int UT::unit_tests<"is_function">(void) {


	std::cout << std::boolalpha;

	std::cout << "is_function<int>::value: "
		<< xns::is_function<int> << std::endl;

	std::cout << "is_function<A>::value: "
		<< xns::is_function<A> << std::endl;

	std::cout << "is_member_function<decltype(&A::print)>::value: "
		<< xns::is_member_function<decltype(&A::print)> << std::endl;

	std::cout << "is_member_function<decltype(print)>::value: "
		<< xns::is_member_function<decltype(print_)> << std::endl;




	return 0;
}

#if defined(XNS_TEST_IS_FUNCTION)
int main(void) {
	return UT::unit_tests<"is_function">();
}
#endif


