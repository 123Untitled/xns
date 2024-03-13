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
#include <algorithm>

// boost
//#include <benchmark/benchmark.h>
//#include <boost/container/set.hpp>

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
		NSIZE = 1'000'00,
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


	std::vector<type> vec = random_vector<false>(NSIZE);

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

	//bench.run("boost insert", [&]() -> void {
	//	for (xns::size_t j = 0; j < ITERATIONS; ++j) {
	//		boost::container::set<type> bset;
	//		for (xns::size_t i = 0; i < NSIZE; ++i) {
	//			bset.insert(vec[i]);
	//			checksum ^= bset.size();
	//		}
	//	}
	//});

	bench.result("insert");
	std::cout << "checksum: " << checksum << std::endl;
	return;

	{
		xns::tree<type> tree;
		std::set<type> set;
		/*
		boost::container::set<type> boost;
		*/
		for (auto n : vec) {
			tree.insert(n);
			set.insert(n);
			//boost.insert(n);
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

		/*
		bench.run("boost contains", [&]() -> void {
			for (auto n : vec) {
				checksum ^= boost.contains(n);
			}
		});
		*/

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

	tree.print();
	tree.fragmentation();
	tree.defragment();
	tree.print();
	tree.fragmentation();
	//tree.fragmentation();
	//tree.print();
	//tree.memory_frag();

	xns::println("AVL size  - ", tree.size(), "\nAVL depth - ", tree.depth());
	check_tree(tree);
	xns::out::render();
}


class toto {
	public:
		//toto() = default;
		toto(const toto&) = default;
		~toto(){}

};


auto unit_tests_tree(void) -> int {

	insert_test();
	//benchmark01();
	//interactive();
	return 0;
}

//template <bool sorted = false>
//auto random_vector_int(const int size) -> std::vector<int> {
//	std::vector<int> vec;
//	for (int i = 0; i < size; ++i)
//		vec.push_back(xns::random::integral<int>());
//	if constexpr (sorted)
//		std::sort(vec.begin(), vec.end());
//	return vec;
//}

//static auto rvector = random_vector_int<false>(1'000'000);
//
//
//static auto _tree(benchmark::State& state) -> void {
//
//	for (auto _ : state) {
//	xns::tree<int> tree;
//		for (auto i = 0; i < state.range(0); ++i) {
//			tree.insert(rvector[(unsigned long)i]);
//			benchmark::DoNotOptimize(tree.size());
//		}
//	}
//}
//
//static auto _set(benchmark::State& state) -> void {
//
//	for (auto _ : state) {
//	std::set<int> set;
//		for (auto i = 0; i < state.range(0); ++i) {
//			set.insert(rvector[(unsigned long)i]);
//			benchmark::DoNotOptimize(set.size());
//		}
//	}
//}
//
//static auto _boost(benchmark::State& state) -> void {
//
//	for (auto _ : state) {
//	boost::container::set<int> bset;
//		for (auto i = 0; i < state.range(0); ++i) {
//			bset.insert(rvector[(unsigned long)i]);
//			benchmark::DoNotOptimize(bset.size());
//		}
//	}
//}
//#define START 100
//#define END 1'000'000
//
//BENCHMARK(_tree)  -> Range(START, END) -> RangeMultiplier(2) -> Unit(benchmark::kMillisecond);
//BENCHMARK(_set)   -> Range(START, END) -> RangeMultiplier(2) -> Unit(benchmark::kMillisecond);
//BENCHMARK(_boost) -> Range(START, END) -> RangeMultiplier(2) -> Unit(benchmark::kMillisecond);
//
	//BENCHMARK_MAIN();

#include "vector3d.hpp"

#if defined(XNS_TEST_TREE)
int main(int argc, char** argv) {

	using vtype = xns::vector3D<float>;

	vtype v1{-2.0f, -2.0f, 0.0f};
	vtype v2{ 1.0f,  0.0f, 0.0f};

	v1.print();
	v2.print();

	auto v3 = xns::reflect(v1, v2);


	v3.print();


	return 0;

	return unit_tests_tree();
}
#endif


