#include "unit_tests.hpp"
#include "vector.hpp"
#include "random.hpp"
#include "time.hpp"



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

static auto simd_test(void) -> void {

	using size_type = typename xns::vector<int>::size_type;

	xns::vector<int> vec;

	constexpr size_type N = 1'000'000;

	for (size_type i = 0; i < N; ++i) {
		vec.push_back(xns::random::integral<int>());
	}

	auto start = xns::time::now();

	for (size_type i = 0; i < 100; ++i) {
		xns::vector<int> vc{vec};
	}

	auto end = xns::time::now();

	std::cout << "copy: " << end - start << " ns" << std::endl;






}


/* unit test */

auto unit_tests_vector(void) -> int {

	simd_test();
	xns::vector<int> v;
	// code here...
	return 0;
}

#if defined(XNS_TEST_VECTOR)
int main(void) { {
	return unit_tests_vector();
}
}
#endif

