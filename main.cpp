#include "xfunc.hpp"

#include <array>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <stack>
#include <any>

#include "random.hpp"

int main(int ac, char** av) {


	//UT::array_ut();

	//UT::tuple_ut();

	for (auto i = 0; i < 10; ++i) {
		std::cout << Xf::Random::random(10) << std::endl;
	}

	return EXIT_SUCCESS;

}





