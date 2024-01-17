#include "unit_tests.hpp"
#include "vector3d.hpp"

/* unit test */
template <>
int UT::unit_tests<"vector3d">(void) {
	return 0;
}

#if defined(XNS_TEST_VECTOR3D)
int main(void) {
	return UT::unit_tests<"vector3d">();
}
#endif

