#include "unit_tests.hpp"
#include "math/vector3d.hpp"



/* unit test */

auto unit_tests_vector3d(void) -> int {

	xns::vector3D<double> v1{2, 3, 4};
	xns::vector3D<double> v2{5, 6, 7};

	auto v3 = xns::normalize(v1);
	auto v4 = xns::dot(v1, v2);
	auto v5 = xns::cross(v1, v2);
	auto v6 = xns::project(v1, v2);
	auto v7 = xns::reflect(v1, v2);

	v1.length();
	v1.normalize();
	v1.x(2.0);

	v3.print();


	return 0;
}

#if defined(XNS_TEST_VECTOR3D)
int main(void) {
	return unit_tests_vector3d();
}
#endif
