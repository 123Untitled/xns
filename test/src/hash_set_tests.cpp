#include "unit_tests.hpp"
#include "hash_set.hpp"

#include "random.hpp"
#include "time.hpp"
#include <unordered_set>

/* unit test */
template <>
bool UT::unit_tests<"hash_set">(void) {

	std::vector<xns::string> xvec{};
	std::vector<std::string> svec{};

	for (xns::size_t i = 0; i < 10000; ++i) {
		xvec.push_back({});
		auto& str = xvec.back();
		for (xns::size_t j = 0; j < 10; ++j) {
			str.append(xns::random::integral<char>());
		}
		svec.push_back({str.data(), str.size()});
	}

		xns::hash_set<xns::string> xset{};
		std::unordered_set<std::string> sset{};

	{
		auto start = xns::time::now();
		for (auto& i : xvec) {
			xset.insert(i);
		}
		auto end = xns::time::now();
		std::cout << "     xns::hash_set -> " << std::right << std::setw(10) << end - start << std::endl;
	}

	{
		auto start = xns::time::now();
		for (auto& i : svec) {
			sset.insert(i);
		}
		auto end = xns::time::now();
		std::cout << "std::unordered_set -> " << std::right << std::setw(10) << end - start << std::endl;
	}

	{
		auto start = xns::time::now();
		for (auto& i : xvec) {
			xset.contains(i);
		}
		auto end = xns::time::now();
		std::cout << "     xns::hash_set -> " << std::right << std::setw(10) << end - start << std::endl;
	}

	{
		auto start = xns::time::now();
		for (auto& i : svec) {
			sset.contains(i);
		}
		auto end = xns::time::now();
		std::cout << "std::unordered_set -> " << std::right << std::setw(10) << end - start << std::endl;
	}

	//set.print();

	// code here...
	return false;
}

int main(void) {
	return UT::unit_tests<"hash_set">()
		? EXIT_SUCCESS : EXIT_FAILURE;
}

