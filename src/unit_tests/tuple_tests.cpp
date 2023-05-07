#include "unit_tests.hpp"



void UT::tuple_ut(void) {

	START_UT("tuple");
	using namespace Xf;



	using Type = Class<int, double, char>;

	Type type{1, 2.0, 'c'};

	Tuple<Type, int, float> t3{Xf::move(type), 2, 3.0f};

	//Tuple<float, char> t02 = t3;

	t3.iterate();

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



}
