#include "unit_tests.hpp"



void UT::tuple_ut(void) {

	START_UT("tuple");
	using namespace Xf;



	using Type = Class<int, float, char>;

	Type type{1, 2.0f, 'c'};

	Tuple<Type> t3{Xf::move(type)};

	auto t4 = t3;

	Tuple t5{123, 99.9, 'c'};

	t3 = t4;

	t3.iterate();
	t4.iterate();
	//t5.iterate();



}
