#include "unit_tests.hpp"
#include "array.hpp"
#include "swap.hpp"
#include "benchmark.hpp"
#include <array>


template <>
bool UT::unit_tests<"array">(void) {

	using Type = Class<int, float, char>;

	xns::array<xns::array<int, 3>, 2> a{
		xns::array<int, 3>{1, 2, 3},
		xns::array<int, 3>{4, 5, 6}
	};

	for (xns::size_t i = 0; i < a.size(); ++i) {
		for (xns::size_t j = 0; j < a[i].size(); ++j) {
			std::cout << a[i][j] << " ";
		}
		std::cout << std::endl;
	}



	xns::array arr1 = {1, 2, 3, 4, 5, 6};

	arr1.for_each([](auto& elem) {
		std::cout << elem << " ";
	});
	std::cout << std::endl;

	arr1.assign(7, 8, 9, 10, 11, 12);

	arr1.for_each([](auto& elem) {
		std::cout << elem << " ";
	});
	std::cout << std::endl;



	xns::array<Type, 3, 2> arr {

		Type{1, 1.0f, 'a'},
		Type{2, 2.0f, 'b'},
		Type{3, 3.0f, 'c'},

		Type{3, 3.0f, 'c'},
		Type{3, 3.0f, 'c'},
		Type{3, 3.0f, 'c'}
	};

	Type t0{1, 1.0f, 'a'};

	arr.assign(
			t0,
		Type{2, 2.0f, 'b'},
		Type{3, 3.0f, 'c'},

		Type{3, 3.0f, 'c'},
		Type{3, 3.0f, 'c'},
		Type{3, 3.0f, 'c'}
	);



	return true;


}


int main(void) {



	return 0;
}
