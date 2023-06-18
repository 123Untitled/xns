#include "unit_tests.hpp"
#include "math.hpp"

template <>
bool UT::unit_tests<"math">() {

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

	double f = (double)xns::max<unsigned int>();

	std::cout << "max: " << f << std::endl;

	f += 0.5f;
	std::cout << "max: " << f << std::endl;

	double ret = xns::ceil(f);

	std::cout << "ceil: " << ret << std::endl;


	return false;
}
