#include "unit_tests.hpp"
#include "hash_set.hpp"

#include "random.hpp"
#include "benchmark.hpp"
#include "time.hpp"
#include <unordered_set>


static xns::size_t check_sum = 0;

/* unit test */
template <>
bool UT::unit_tests<"hash_set">(void) {

	constexpr size_t N = 1000;
	constexpr size_t S = 1000;



	xns::benchmark<8> bench;

	bench.run("xns::hash_map", [&] {
		xns::hash_set<xns::string> xset{};
		for (xns::size_t i = 0; i < N; ++i) {
			xns::string str{};
			for (xns::size_t j = 0; j < S; ++j) {
				str.append(xns::random::integral<char>());
				check_sum ^= str.back();
			}
			// xset.insert(str);
			// check_sum ^= xset.size();
		}
	});

	bench.run("std::unordered_map", [&] {
		std::unordered_set<std::string> sset{};
		for (xns::size_t i = 0; i < N; ++i) {
			std::string str{};
			for (xns::size_t j = 0; j < S; ++j) {
				str.push_back(xns::random::integral<char>());
				check_sum ^= str.back();
			}
			// sset.insert(str);
			// check_sum ^= sset.size();

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
	return false;
}

int main(void) {
	return UT::unit_tests<"hash_set">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}
