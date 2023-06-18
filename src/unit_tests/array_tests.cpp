#include "unit_tests.hpp"
#include "array.hpp"


template <size_t... I, size_t... J>
void test(xns::index_seq<I...> i, xns::index_seq<J...> j) {
	xns::debug_sequence(i);
	xns::debug_sequence(j);
}

template <class... A>
auto make(A&&... args) {

	using RType = xns::array<xns::pack_type<0, A...>, sizeof...(A)>;

	return RType{xns::forward<A>(args)...};
}

template <>
bool UT::unit_tests<"array">(void) {


	//test(Xf::make_index_range_step<0, 10, 2>{}, Xf::make_index_range_step<0, 10, 2>{});
	//return;

	using namespace Xf;
	/*
	Array<Array<int, 2>, 3> a{
		Array<int, 2>{1, 2},
		Array<int, 2>{3, 4},
		Array<int, 2>{5, 6}
	};*/


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


	xns::array<xns::array<Type, 3>, 2> arr0 {

		xns::array<Type, 3>{
			Type{1, 1.0f, 'a'},
			Type{2, 2.0f, 'b'},
			Type{3, 3.0f, 'c'}
		},

			xns::array<Type, 3>{
			Type{4, 4.0f, 'd'},
			Type{5, 5.0f, 'e'},
			Type{6, 6.0f, 'f'}
		},

	};






	xns::array<Type, 3, 2> arr {

		Type{1, 1.0f, 'a'},
		Type{2, 2.0f, 'b'},
		Type{3, 3.0f, 'c'},

		Type{3, 3.0f, 'c'},
		Type{3, 3.0f, 'c'},
		Type{3, 3.0f, 'c'}
	};


	return true;


}
