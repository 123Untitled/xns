#include "unit_tests.hpp"
#include "safe_enum.hpp"


struct def {
	using type = int;

	enum enum_type : type {
		MAX = 9
	};
};

using safe = xns::safe_enum<def>;


/* unit test */
template <>
int UT::unit_tests<"safe_enum">(void) {

	safe s1 = safe::MAX;



	// code here...
	return 0;
}

#if defined(XNS_TEST_SAFE_ENUM)
int main(void) {
	return UT::unit_tests<"safe_enum">();
}
#endif

