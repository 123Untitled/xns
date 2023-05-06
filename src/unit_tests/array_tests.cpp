#include "unit_tests.hpp"

template <size_t... I, size_t... J>
void test(Xf::IndexSeq<I...> i, Xf::IndexSeq<J...> j) {
	Xf::debug_sequence(i);
	Xf::debug_sequence(j);
}

template <class... A>
auto make(A&&... args) {

	using RType = Xf::Array<Xf::PackType_t<0, A...>, sizeof...(A)>;

	return RType{Xf::forward<A>(args)...};
}

void UT::array_ut(void) {

	//test(Xf::make_index_range_step<0, 10, 2>{}, Xf::make_index_range_step<0, 10, 2>{});
	//return;

	using namespace Xf;
	/*
	Array<Array<int, 2>, 3> a{
		Array<int, 2>{1, 2},
		Array<int, 2>{3, 4},
		Array<int, 2>{5, 6}
	};*/

	START_UT("array");

	//Array<int, 3> tab{1, 2, 3};

	//SizeT i = 0;
	//tab(i);


	using Type = Class<int, float, char>;


	/*
	Array<Type, 2, 3> arr {
		Type{1, 1.0f, 'a'}, Type{2, 2.0f, 'b'},
		Type{3, 3.0f, 'c'}, Type{4, 4.0f, 'd'}




	};
	*/


	Array<Array<Type, 3>, 2> arr0 {

		Array<Type, 3>{
			Type{1, 1.0f, 'a'},
			Type{2, 2.0f, 'b'},
			Type{3, 3.0f, 'c'}
		},

		Array<Type, 3>{
			Type{4, 4.0f, 'd'},
			Type{5, 5.0f, 'e'},
			Type{6, 6.0f, 'f'}
		},

	};






	Xf::Array<Type, 3, 2> arr {

		Type{1, 1.0f, 'a'},
		Type{2, 2.0f, 'b'},
		Type{3, 3.0f, 'c'},

		Type{3, 3.0f, 'c'},
		Type{3, 3.0f, 'c'},
		Type{3, 3.0f, 'c'}
	};




}
