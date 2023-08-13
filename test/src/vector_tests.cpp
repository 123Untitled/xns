#include "unit_tests.hpp"
#include "vector.hpp"



static void dichotic_test(void) {
	xns::vector<int> v = xns::make_vector<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

	// initialize seed
	std::srand((unsigned)std::time(nullptr));

	xns::vector<int> vvv{};
	for (int i = 0; i < 100; ++i) {
		//vvv.copy_back(std::rand() % 1000);
		vvv.dichotomic_insert(std::rand() % 100000);
	}

	for (auto& i : vvv) {
		std::cout << i << ", ";
	}
	std::cout << std::endl;


	auto it = vvv.dichotomic_search(1000);

	if (it != vvv.end()) {
		std::cout << "found: " << *it << std::endl;
	} else {
		std::cout << "not found" << std::endl;
	}
}



/* unit test */
template <>
bool UT::unit_tests<"vector">(void) {

	xns::vector<int> v;
	// code here...
	return false;
}

int main(void) {
	UT::unit_tests<"vector">();
	return 0;
}
