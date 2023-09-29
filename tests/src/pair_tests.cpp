#include "unit_tests.hpp"
#include "pair.hpp"


#include "tuple.hpp"

/* unit test */
template <>
bool UT::unit_tests<"pair">(void) {


	//auto [


	xns::pair<int, float> pair{2, 0.3f};

	xns::pair<int, int> pair3{2, 3};

	int& i2 = xns::get<1>(pair3);

	//int i = std::get<int>(pair2);

	float& i = xns::get<float>(pair);

	//auto& [a, b] = pair;


	// code here...
	return false;
}


int main(void) {




	UT::unit_tests<"pair">();

	return 0;
}

