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
bool UT::unit_tests<"safe_enum">(void) {

	safe s1 = safe::MAX;



	// code here...
	return false;
}

int main(void) {



	UT::unit_tests<"safe_enum">();


	return 0;
}
