#include "unit_tests.hpp"
#include "other/safe_enum.hpp"


struct def {
	using type = int;

	enum enum_type : type {
		MAX = 9
	};
};

using safe = xns::safe_enum<def>;


/* unit test */

auto unit_tests_safe_enum(void) -> int {

	safe s1 = safe::MAX;



	// code here...
	return 0;
}

#if defined(XNS_TEST_SAFE_ENUM)
int main(void) {
	return unit_tests_safe_enum();
}
#endif

