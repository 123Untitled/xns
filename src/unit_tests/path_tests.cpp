#include "unit_tests.hpp"

#include <filesystem>

// this is a unit test to compare simplified path resolution with std::filesystem

bool UT::path_ut(void) {

	// original path
	const char* str = "../../xns/../../../../lib/log.txt/.";

	std::cout << "original path: " << str << std::endl;

	// simplified path
	xns::path p1{str};

	// print simplified path
	std::cout << "simplified path: ";
	for (xns::path::size_type x = 0; x < p1.count(); ++x) {
		std::cout << p1[x].get<0>().pointer();
		if (x < p1.count() - 1) {
			std::cout << "/"; }
	} std::cout << std::endl;


	return true;
}
