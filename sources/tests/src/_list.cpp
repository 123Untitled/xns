#include "unit_tests.hpp"
#include "list.hpp"

#include <unistd.h>
//#include <vector>
#include <list>

//#include "benchmark.hpp"
#include "random.hpp"


static xns::size_t NSIZE = 100000;
static xns::size_t check_sum = 0;

//static auto benchmark(void) -> void {
//
//	xns::benchmark<5> bench{};
//
//	xns::list<int> xlist;
//	for (xns::size_t i = 0; i < NSIZE; ++i)
//		xlist.push_back(xns::random::integral<int>());
//	std::list<int> slist;
//	for (xns::size_t i = 0; i < NSIZE; ++i)
//		slist.push_back(xns::random::integral<int>());
//
//
//	bench.run("xns::list push_back", []() -> void {
//
//		xns::list<int> local_list;
//		for (xns::size_t i = 0; i < NSIZE; ++i) {
//			local_list.push_back(xns::random::integral<int>());
//			check_sum ^= local_list.back();
//		}
//	});
//
//	bench.run("std::list push_back", []() -> void {
//
//		std::list<int> local_list;
//		for (xns::size_t i = 0; i < NSIZE; ++i) {
//			local_list.push_back(xns::random::integral<int>());
//			check_sum ^= local_list.back();
//		}
//	});
//
//	bench.result("push_back");
//
//	bench.run("xns::list reverse", [&xlist]() -> void {
//
//			xlist.reverse();
//			check_sum ^= xlist.front();
//	});
//
//	bench.run("std::list reverse", [&slist]() -> void {
//
//			slist.reverse();
//			check_sum ^= slist.front();
//	});
//
//	bench.result("reverse");
//
//
//	bench.run("xns::list copy", [&xlist]() -> void {
//			xns::list<int> local_list{xlist};
//			check_sum ^= local_list.front();
//	});
//
//	bench.run("std::list copy", [&slist]() -> void {
//			std::list<int> local_list{slist};
//			check_sum ^= local_list.front();
//	});
//
//	bench.result("copy");
//
//
//
//
//	std::cout << "check_sum: " << check_sum << std::endl;
//
//
//
//
//
//}
//

/* unit test */
template <>
int UT::unit_tests<"list">(void) {

	//benchmark();
	return 0;
	xns::list<const int> list;

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_front(0);
	list.push_front(-1);
	list.push_front(-2);


	for (const auto& ref : list) {
		const int& ref2 = ref;
		std::cout << ref2 << std::endl;
	}

	list.reverse();
	std::cout << "reverse" << std::endl;

	for (const auto& ref : list) {
		const int& ref2 = ref;
		std::cout << ref2 << std::endl;
	}

	return 0;





	xns::list<const int>::iterator it = list.begin();

	while (it != list.end()) {
		std::cout << *it << std::endl;
		++it;
	}

	xns::list<const int>::const_iterator cit = list.begin();

	while (cit != list.end()) {
		const int& ref = *cit;

		std::cout << *cit << std::endl;
		++cit;
	}


	const int a = 1;
	int b = 2;
	int* cp = &b;
	const int* cpc = &b;
	const int& ar = a;

	xns::list<int> list2 = xns::make_list(a, b, *cp, *cpc, ar);

	xns::list<int>::iterator it2 = list2.begin();

	::write(1, "\n", 1);
	::write(1, "\n", 1);

	while (it2 != list2.end()) {
		std::cout << *it2 << std::endl;
		++it2;
	}
	::write(1, "\n", 1);
	::write(1, "\n", 1);

	// expected print:
	std::cout << "1" << std::endl;
	std::cout << "2" << std::endl;
	std::cout << "2" << std::endl;
	std::cout << "2" << std::endl;
	std::cout << "1" << std::endl;






	std::cout << list.front() << std::endl;
	std::cout << list.back() << std::endl;

	list.pop_back();

	std::cout << list.back() << std::endl;



	// code here...
	return 0;
}




#include <benchmark/benchmark.h>

template <typename T>
void launch_bench(benchmark::State& state) {

	using type = typename T::value_type;

	for (auto _ : state) {
		T list;
		for (int i = 0; i < state.range(0); ++i) {
			list.push_back(static_cast<type>(i));
		}
	}

	//state.SetItemsProcessed(state.iterations() * state.range(0));
}

#define RANGE 1'000'000

BENCHMARK(launch_bench<xns::list<xns::size_t>>)->Name("xns")->Range(8, RANGE)->Unit(benchmark::kMillisecond);
BENCHMARK(launch_bench<std::list<xns::size_t>>)->Name("std")->Range(8, RANGE)->Unit(benchmark::kMillisecond);

#if defined(XNS_TEST_LIST)
BENCHMARK_MAIN();
//int main(void) {
//	return UT::unit_tests<"list">();
//}
#endif

