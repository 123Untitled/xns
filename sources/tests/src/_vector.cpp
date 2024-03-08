#include "vector.hpp"
//#include <benchmark/benchmark.h>
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

class A {
public:
	A(void) = default;
	A(const A&) = default;
	A(A&&) noexcept(false) = default;
	A& operator=(const A&) = default;
	A& operator=(A&&) = default;
	~A(void) = default;
};

#include "malloc.hpp"

/* unit test */
auto unit_tests_vector(void) -> int {

	//simd_test();

	//xns::vector<A> v;
	//xns::malloc();


	return 0;
}


#include <vector>

#if defined(XNS_TEST_VECTOR)
int main(void) {
	return unit_tests_vector();
}
#endif



//template <typename T>
//static auto _test_(benchmark::State& state) -> void {
//
//		T v1;
//	for (auto _ : state) {
//		v1.clear();
//		for (auto i = 0; i < state.range(0); ++i) {
//			v1.emplace_back(xns::random::integral<int>());
//			benchmark::DoNotOptimize(v1.size());
//		}
//	}
//}
//
//#define START 100
//#define END 10'000'000
//#define REPEAT 1
//
//BENCHMARK(_test_<std::vector<int>>)  -> Range(START, END) -> Repetitions(REPEAT) -> RangeMultiplier(2) -> Unit(benchmark::kMillisecond);
//BENCHMARK(_test_<xns::vector<int>>)  -> Range(START, END) -> Repetitions(REPEAT) -> RangeMultiplier(2) -> Unit(benchmark::kMillisecond);
//
//BENCHMARK_MAIN();
