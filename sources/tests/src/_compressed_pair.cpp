#include "containers/compressed_pair.hpp"
#include "containers/pair.hpp"
#include <iostream>

//#include <benchmark/benchmark.h>

// google benchmark learn




struct mypair {
	int a;
	int b;
};

#include "other/benchmark.hpp"
#include "random/random.hpp"

//template <typename T>
//static auto compressed_pair(benchmark::State& state) -> void {
//	std::vector<T> vec;
//	vec.resize((unsigned long)state.range(0));
//
//	for (auto _ : state) {
//		for (auto i = 0; i < state.range(0); ++i) {
//			vec[(unsigned long)i] = T{xns::random::integral<int>(), xns::random::integral<int>()};
//			benchmark::DoNotOptimize(vec[(unsigned long)i]);
//		}
//	}
//}
//
//static auto pair(benchmark::State& state) -> void {
//	std::vector<xns::pair<int, int>> vec;
//	vec.resize((unsigned long)state.range(0));
//
//	for (auto _ : state) {
//		for (auto i = 0; i < state.range(0); ++i) {
//			xns::pair<int, int> p;
//			p._first = xns::random::integral<int>();
//			p._second = xns::random::integral<int>();
//			vec[(unsigned long)i] = p;
//			benchmark::DoNotOptimize(vec[(unsigned long)i]);
//		}
//	}
//}
//
//static auto mypair(benchmark::State& state) -> void {
//	std::vector<struct mypair> vec;
//	vec.resize((unsigned long)state.range(0));
//
//	for (auto _ : state) {
//		for (auto i = 0; i < state.range(0); ++i) {
//			struct mypair p;
//			p.a = xns::random::integral<int>();
//			p.b = xns::random::integral<int>();
//			vec[(unsigned long)i] = p;
//			benchmark::DoNotOptimize(vec[(unsigned long)i]);
//		}
//	}
//}
//
//#define START 1000
//#define END 1'000'000
//
////BENCHMARK(compressed_pair<xns::pair2<int, int>>) -> Range(START, END) -> RangeMultiplier(2) ->  Unit(benchmark::kMillisecond);
////BENCHMARK(compressed_pair<std::pair<int, int>>) -> Range(START, END) -> RangeMultiplier(2) ->  Unit(benchmark::kMillisecond);
//BENCHMARK(pair) -> Range(START, END) -> RangeMultiplier(2) ->  Unit(benchmark::kMillisecond);
//BENCHMARK(mypair) -> Range(START, END) -> RangeMultiplier(2) ->  Unit(benchmark::kMillisecond);
//

/* unit test */
auto unit_tests_compressed_pair(void) -> int {


	return 0;
}

	//BENCHMARK_MAIN();
#if defined(XNS_TEST_COMPRESSED_PAIR)
int main(void) {
	return unit_tests_compressed_pair();
}
#endif

