#include "unit_tests.hpp"
#include "tuple.hpp"

const int&& foo(void) {

	static int i = 0;

	return xns::move(i);
}

template <>
bool UT::unit_tests<"tuple">(void) {

	xns::tuple<int, int> t1{1, 2};

	xns::get<1>(t1);


	xns::tuple<int, float, const char*> _tuple{2, 0.3f, "hello"};

	int refff = xns::get<int>(xns::move(_tuple));

	static_assert(xns::is_unique<char, int, float, const char*>);


	//int& reff = xns::get<1>(_tuple);


	//_tuple.set<0>(2);


	//auto ret = xns::get<float>(_tuple);

	//std::cout << ret << std::endl;

	return false;




	//std::cout << refff << std::endl;


	using Type = Class<int, double, char>;

	Type type{1, 2.0, 'c'};

	xns::tuple<Type, int, float> t3{xns::move(type), 2, 3.0f};

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

	return true;

}


int main(void) {


	UT::unit_tests<"tuple">();

	return 0;

}
