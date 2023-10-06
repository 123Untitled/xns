#include "unit_tests.hpp"
#include "math.hpp"
#include <cmath>
#include "integer.hpp"
#include "bit_view.hpp"
#include "integer_arithmetic.hpp"

template <>
int UT::unit_tests<"math">() {

	float f1 = 1.4f;
	float f2 = -1.4f;
	float f3 = 1.6f;
	float f4 = -1.6f;

	std::cout << "floor +1.4f: " << std::floor(f1) << " | " << xns::floor(f1) << std::endl;
	std::cout << "floor -1.4f: " << std::floor(f2) << " | " << xns::floor(f2) << std::endl;
	std::cout << "floor +1.6f: " << std::floor(f3) << " | " << xns::floor(f3) << std::endl;
	std::cout << "floor -1.6f: " << std::floor(f4) << " | " << xns::floor(f4) << std::endl;

	std::cout << "ceil  +1.4f: " << std::ceil(f1) << " | " << xns::ceil(f1) << std::endl;
	std::cout << "ceil  -1.4f: " << std::ceil(f2) << " | " << xns::ceil(f2) << std::endl;
	std::cout << "ceil  +1.6f: " << std::ceil(f3) << " | " << xns::ceil(f3) << std::endl;
	std::cout << "ceil  -1.6f: " << std::ceil(f4) << " | " << xns::ceil(f4) << std::endl;

	unsigned int nn = 259;

	std::cout << static_cast<int>(static_cast<unsigned char>(nn)) << std::endl;

	double f = (double)xns::limits::max<unsigned int>();

	std::cout << "max: " << f << std::endl;

	f += 0.5f;
	std::cout << "max: " << f << std::endl;

	double ret = xns::ceil(f);

	std::cout << "ceil: " << ret << std::endl;


	return false;
}

static void func() {

	using C = unsigned char;
	using S = unsigned short;
	using I = unsigned int;

	const char* types[3] = {"C", "S", "I"};

	// init random seed
	srand((unsigned int)time(NULL));


	for (int i = 0; i < 1000; ++i) {

		int a = rand() % 3;
		int b = rand() % 3;
		int c = rand() % 3;

		std::cout << "xns::arithmetic<"
				  << types[a] << ", "
				  << types[b] << ", "
				  << types[c] << ">::addition(0,0);"
				  << std::endl;
	}
}



void generateComparisons(void) {
	std::vector<int> nums = {1, 2, 3};
    do {
		std::cout << nums[0] << " < " << nums[1] << " < " << nums[2] << std::endl;
		std::cout << nums[0] << " = " << nums[1] << " < " << nums[2] << std::endl;
		std::cout << nums[0] << " < " << nums[1] << " = " << nums[2] << std::endl << std::endl;
		//std::cout << nums[0] << " = " << nums[1] << " = " << nums[2] << std::endl << std::endl;
    } while (std::next_permutation(nums.begin(), nums.end()));
}

#if defined(XNS_TEST_MATH)
int main(void) {
	return UT::unit_tests<"math">();
}
#endif

