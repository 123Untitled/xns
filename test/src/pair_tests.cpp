#include "unit_tests.hpp"
#include "pair.hpp"


#include "tuple.hpp"

/* unit test */
template <>
bool UT::unit_tests<"pair">(void) {


	//auto [


	xns::pair<int, float> pair{2, 0.3f};
	std::pair<int, float> pair2{2, 0.3f};

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

