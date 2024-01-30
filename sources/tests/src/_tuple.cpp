#include "unit_tests.hpp"
#include "tuple.hpp"
#include <tuple>

const int&& foo(void) {

	static int i = 0;

	return xns::move(i);
}


auto unit_tests_tuple(void) -> int {

	int i = 0;
	float f = 0.0f;

	xns::tuple t0{i, f};
	xns::tuple t1{0, 0.0f};

	t0 = t1; // here error



	//
	//xns::get<0>(t0) = 1;
	//std::get<0>(t1) = 1;
	//
	//std::cout << "sizeof: " << sizeof(t0) << std::endl;
	//std::cout << "sizeof: " << sizeof(t1) << std::endl;
	return 0;



	xns::tuple<int> t3{1};

	//const auto& v = xns::get<1>(xns::move(t1));


	xns::tuple<int, float, const char(&)[6]> _tuple = xns::make_tuple(1, 2.0f, "hello");

	int refff = xns::get<int>(xns::move(_tuple));

	static_assert(xns::is_unique<char, int, float, const char*>);


	int& reff = xns::get<0>(_tuple);


	//_tuple.set<0>(2);


	//auto ret = xns::get<float>(_tuple);

	//std::cout << ret << std::endl;

	return 0;




	//std::cout << refff << std::endl;



	//Type type{1, 2.0, 'c'};

	//xns::tuple<Type, int, float> t3{xns::move(type), 2, 3.0f};

	//Tuple<float, char> t02 = t3;

	//t3.iterate();

	//Tuple<Type, int, float> t4 = {2, 3.0f, 'c'};

	//Tuple<Type, int> t3{};


	//Tuple<Type, int> t4 = t3;

	//auto t4 = t3;

   // Tuple<Type> t4 = t3;

	//Tuple t5{123, 99.9, 'c'};

	//t3 = t4;

	//t3.iterate();
	//t4.iterate();
	//t5.iterate();

	return 0;

}


#if defined(XNS_TEST_TUPLE)
int main(void) {
	return unit_tests_tuple();
}
#endif

