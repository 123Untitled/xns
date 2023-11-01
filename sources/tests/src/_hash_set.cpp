#include "unit_tests.hpp"
#include "hash_set.hpp"

#include "random.hpp"
#include "benchmark.hpp"
#include "time.hpp"
#include <unordered_set>
#include "trie.hpp"


static xns::size_t check_sum = 0;

/* unit test */
template <>
int UT::unit_tests<"hash_set">(void) {

	std::cout << "sizeof xns::unordered_set<std::string>: " << sizeof(xns::unordered_set<std::string>) << std::endl;
	std::cout << "sizeof std::unordered_set<std::string>: " << sizeof(std::unordered_set<std::string>) << std::endl;

	constexpr size_t N = 10000;
	constexpr size_t S = 128;

	float load = 0.75f;

	xns::benchmark<8> bench;

	bench.run("xns::unordered_set", [&] {
		xns::unordered_set<std::string> xset{};
		xset.max_load_factor(load);
		for (xns::size_t i = 0; i < N; ++i) {
			std::string str{};
			for (xns::size_t j = 0; j < S; ++j) {
				str.push_back(xns::random::integral<char>());
				check_sum ^= str.back();
			}
			xset.insert(str);
			check_sum ^= xset.size();
		}


		//xns::unordered_set<std::string>::collisions();

	});

	bench.run("std::unordered_set", [&] {
		std::unordered_set<std::string> sset{};
		sset.max_load_factor(load);
		for (xns::size_t i = 0; i < N; ++i) {
			std::string str{};
			for (xns::size_t j = 0; j < S; ++j) {
				str.push_back(xns::random::integral<char>());
				check_sum ^= str.back();
			}
			sset.insert(str);
			check_sum ^= sset.size();

		}
	});

	bench.result("insert");




	// bench.run("xns::hash_map", [&] {
	// });
	//
	// bench.run("std::unordered_map", [&] {
	// });
	//
	// bench.result("contains");

	std::cout << "check_sum: " << check_sum << std::endl;


	// code here...
	return 0;
}

#if defined(XNS_TEST_HASH_SET)
int main(void) {
	return UT::unit_tests<"hash_set">();
}
#endif


