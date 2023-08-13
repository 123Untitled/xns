#include "unit_tests.hpp"
#include "tuple.hpp"


template <>
bool UT::unit_tests<"tuple">(void) {

	using namespace xns;


	xns::tuple<int, float, const char*> _tuple{1, 0.3f, "hello"};

	//_tuple.set<8>(2);


	//auto ret = xns::get<float>(_tuple);

	//std::cout << ret << std::endl;

	return false;


	auto& refff = xns::get<0>(_tuple);

	std::cout << refff << std::endl;


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

