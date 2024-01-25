#include "unit_tests.hpp"
#include "is_union.hpp"

class test_class {
	union {
		int u;
		float f;
	};
};

union test_union {
	int i;
	float f;

};

void test_function(void) {
}

enum test_enum {
	one,
	two,
	three
};

/* unit test */

auto unit_tests_is_union(void) -> int {

	// is_union

	int i = 0;
	test_class c;
	test_union u;

	auto func = test_function;

	std::cout << "is_union [int]: " << xns::is_union<int> << std::endl;
	std::cout << "is_union [test_class]: " << xns::is_union<test_class> << std::endl;
	std::cout << "is_union [test_union]: " << xns::is_union<test_union> << std::endl;
	std::cout << "is_union [test_enum]: " << xns::is_union<test_enum> << std::endl;
	std::cout << "is_union [void(*)()]: " << xns::is_union<decltype(func)> << std::endl;





	return 0;
}

#if defined(XNS_TEST_IS_UNION)
int main(void) {
	return unit_tests_is_union();
}
#endif

