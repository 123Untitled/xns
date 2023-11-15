// local headers
#include "unit_tests.hpp"
#include "tree.hpp"
#include "random.hpp"
#include "time.hpp"
#include "numeric_limits.hpp"
#include "input.hpp"
#include "escape.hpp"
#include "memcpy.hpp"
#include "benchmark.hpp"
#include "file.hpp"

// boost
#include <boost/container/set.hpp>
// google benchmark
//#include <benchmark/benchmark.h>

// standard library
#include <set>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <map>


template <bool sorted = false>
auto random_vector(const xns::size_t size) -> std::vector<xns::size_t> {
	std::vector<xns::size_t> vec;
	for (xns::size_t i = 0; i < size; ++i)
		vec.push_back(xns::random::integral<xns::size_t>());
	if constexpr (sorted)
		std::sort(vec.begin(), vec.end());
	return vec;
}


static void test_iterators(void) {

	xns::tree<int> tree {};

	for (xns::size_t i = 0; i < 1'000'000; ++i) {
		tree.insert(xns::random::integral<int>());
	}

	constexpr xns::size_t N = 10;

	{
		auto start = xns::time::now();
		// bfs iterator
		for (xns::size_t i = 0; i < N; ++i) {
			auto it = tree.bfs_begin();
			while (it) { ++it; }
		}
		auto end = xns::time::now();
		std::cout << "       bfs iterator -> " << end - start << std::endl;
	}

	{
		auto start = xns::time::now();
		// pre-order iterator
		for (xns::size_t i = 0; i < N; ++i) {
			auto it = tree.pre_order_begin();
			while (it) { ++it; }
		}
		auto end = xns::time::now();
		std::cout << " pre-order iterator -> " << end - start << std::endl;
	}

	{
		auto start = xns::time::now();
		// in-order iterator
		for (xns::size_t i = 0; i < N; ++i) {
			auto it = tree.in_order_begin();
			while (it) { ++it; }
		}
		auto end = xns::time::now();
		std::cout << "  in-order iterator -> " << end - start << std::endl;
	}

	{
		auto start = xns::time::now();
		// post-order iterator
		for (xns::size_t i = 0; i < N; ++i) {
			auto it = tree.post_order_begin();
			while (it) { ++it; }
		}
		auto end = xns::time::now();
		std::cout << "post-order iterator -> " << end - start << std::endl;
	}


}


static void benchmark01(void) {

	using type = xns::size_t;

	enum : xns::size_t {
		NSIZE = 1'000'000,
		ITERATIONS = 1,
		RANGE = 1000000000
	};

	xns::benchmark<6> bench;
	xns::size_t checksum = 0;

	//{
	//	xns::tree<type> tree;
	//	std::set<type> set;
	//	boost::container::set<type> boost;
	//	auto vec = random_vector<true>(NSIZE);
	//
	//	for (auto n : vec) {
	//		tree.insert(n);
	//		set.insert(n);
	//		boost.insert(n);
	//	}
	//
	//	bench.run("xns inorder", [&]() -> void {
	//		for (auto it = tree.in_order_begin(); it; ++it) {
	//			checksum ^= *it;
	//		}
	//	});
	//
	//	bench.run("std inorder", [&]() -> void {
	//		for (auto it = set.begin(); it != set.end(); ++it) {
	//			checksum ^= *it;
	//		}
	//	});
	//
	//	bench.run("boost inorder", [&]() -> void {
	//		for (auto it = boost.begin(); it != boost.end(); ++it) {
	//			checksum ^= *it;
	//		}
	//	});
	//
	//	//tree.defragment();
	//
	//}
	//
	//bench.result("in order iterator");
	//std::cout << "checksum: " << checksum << std::endl;
	//return;
	//
	//


	std::vector<type> vec = random_vector<true>(NSIZE);

	bench.run("xns::tree insert", [&]() -> void {
		for (xns::size_t j = 0; j < ITERATIONS; ++j) {
			xns::tree<type> tree;
			for (xns::size_t i = 0; i < NSIZE; ++i) {
				tree.insert(vec[i]);
				checksum ^= tree.size();
			}
			//tree.memory_frag();
		}
	});

	bench.run("std::set insert", [&]() -> void {
		for (xns::size_t j = 0; j < ITERATIONS; ++j) {
			std::set<type> sset;
			for (xns::size_t i = 0; i < NSIZE; ++i) {
				sset.insert(vec[i]);
				checksum ^= sset.size();
			}
		}
	});

	bench.run("boost insert", [&]() -> void {
		for (xns::size_t j = 0; j < ITERATIONS; ++j) {
			boost::container::set<type> bset;
			for (xns::size_t i = 0; i < NSIZE; ++i) {
				bset.insert(vec[i]);
				checksum ^= bset.size();
			}
		}
	});

	bench.result("insert");
	std::cout << "checksum: " << checksum << std::endl;
	return;

	{
		xns::tree<type> tree;
		std::set<type> set;
		boost::container::set<type> boost;
		for (auto n : vec) {
			tree.insert(n);
			set.insert(n);
			boost.insert(n);
		}

		bench.run("xns contains", [&]() -> void {
			for (auto n : vec) {
				checksum ^= tree.contains(n);
			}
		});

		bench.run("std contains", [&]() -> void {
			for (auto n : vec) {
				checksum ^= set.contains(n);
			}
		});

		bench.run("boost contains", [&]() -> void {
			for (auto n : vec) {
				checksum ^= boost.contains(n);
			}
		});

	}



	bench.result("contains");
	std::cout << "checksum: " << checksum << std::endl;


}


/* insert */
static auto insert_test(void) -> void {

	using type = xns::size_t;
	constexpr xns::size_t NSIZE = 50;

	xns::tree<type> tree;

	std::vector<type> vec = random_vector<false>(NSIZE);

	for (auto n : vec)
		tree.insert(n % 100);
		//tree.insert(n % 100);

	//tree.fragmentation();
	//tree.defragment();
	tree.print();
	//tree.fragmentation();
	//tree.print();
	//tree.memory_frag();

	xns::println("AVL size  - ", tree.size(), "\nAVL depth - ", tree.depth());
	check_tree(tree);
	xns::out::render();
}



template <>
int UT::unit_tests<"tree">(void) {


	//auto vec = random_vector<false>(10);
	//xns::tree<xns::size_t> tree;
	//for (auto v : vec)
	//	tree.insert(v);


	insert_test();
	//benchmark01();
	//interactive();
	return 0;
}


			//type v = xns::random::integral<type>();
			//state.ResumeTiming();
			//state.PauseTiming();
	//state.SetItemsProcessed(state.iterations() * state.range(0));
		//state.PauseTiming();

//static xns::vector<xns::size_t> vec;
//
//template <typename T>
//void launch_bench(benchmark::State& state) {
//
//
//	using type = typename T::value_type;
//
//	for (auto _ : state) {
//		T tree;
//		for (int i = 0; i < state.range(0); ++i) {
//			tree.insert(vec[i]);
//			auto size = tree.size();
//			benchmark::DoNotOptimize(tree.size());
//		}
//	}
//	state.SetItemsProcessed(state.iterations() * state.range(0));
//}
//
//
//#define RANGE 1'000'00
//#define NUMBERS RANGE
//#define ITERATIONS 30
//
//using type = xns::size_t;
//using txns = xns::tree<type>;
//using tstd = std::set<type>;
//using tboo = boost::container::set<type>;
//
//
//
//BENCHMARK(launch_bench<txns>)->Name("xns")->Range(8, RANGE)->Iterations(ITERATIONS);
//BENCHMARK(launch_bench<tstd>)->Name("std")->Range(8, RANGE)->Iterations(ITERATIONS);
//BENCHMARK(launch_bench<tboo>)->Name("boost")->Range(8, RANGE)->Iterations(ITERATIONS);
//
//struct ss {
//	char c[21];
//} __attribute__((packed));
//
//
#include "bjorklund.hpp"


#if defined(XNS_TEST_TREE)
//BENCHMARK_MAIN();
int main(int argc, char** argv) {







	//xns::tree<type> tree;
	//
	//tree.insert(2U);
	//tree.insert(7U);
	//tree.insert(5U);
	//tree.insert(4U);
	//tree.insert(1U);
	//tree.insert(8U);
	//tree.insert(6U);
	//tree.insert(3U);
	//tree.insert(0U);
	//
	//for (auto v : tree)
	//	std::cout << v << " ";
	//std::cout << std::endl;
	//return 0;


	//{
	//	//xns::tree<type> tr;
	//	for (xns::size_t i = 0; i < NUMBERS; ++i) {
	//		vec.push_back(xns::random::integral<type>());
	//		//tr.insert(xns::random::integral<type>());
	//	}
	//	//for (auto it = tr.in_order_begin(); it; ++it) {
	//	//	vec.push_back(*it);
	//	//}
	//	//tr.clear();
	//}
	//benchmark::Initialize(&argc, argv);
	//benchmark::RunSpecifiedBenchmarks();

	//xns::benchmark<6> bench;
	//xns::size_t check_sum = 0;
	//
	//bench.run("xns pool allocator", [&]() -> void {
	//	for (xns::size_t i = 0; i < 1000000; ++i) {
	//		auto ptr = xns::memory::pool<ss>::allocate();
	//		check_sum ^= reinterpret_cast<xns::size_t>(ptr);
	//		//xns::memory::pool<ss>::deallocate(ptr);
	//	}
	//});
	//bench.run("xns allocator (malloc)", [&]() -> void {
	//	for (xns::size_t i = 0; i < 1000000; ++i) {
	//		auto ptr = std::allocator<ss>{}.allocate(1);
	//		check_sum ^= reinterpret_cast<xns::size_t>(ptr);
	//		//std::allocator<ss>{}.deallocate(ptr, 1);
	//	}
	//});
	//
	//bench.result("allocators");
	//std::cout << "checksum: " << check_sum << std::endl;

	//return 0;
	return UT::unit_tests<"tree">();
	return 0;
}
#endif


