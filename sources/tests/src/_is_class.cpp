#include "unit_tests.hpp"
#include "type_traits/type_categories/is_class.hpp"

class test_class {
	int u;
};

struct test_struct {
	float f;
};

union test_union {
	int i;
	float f;
};

void test_function_is_class(void) {
}

enum test_enum {
	one,
	two,
	three
};

/* unit test */

auto unit_tests_is_class(void) -> int {

	std::cout << "is_class [int]: " << xns::is_class<int> << std::endl;
	std::cout << "is_class [test_class]: " << xns::is_class<test_class> << std::endl;
	std::cout << "is_class [test_struct]: " << xns::is_class<test_struct> << std::endl;
	std::cout << "is_class [test_union]: " << xns::is_class<test_union> << std::endl;
	std::cout << "is_class [test_enum]: " << xns::is_class<test_enum> << std::endl;
	std::cout << "is_class [void(*)()]: " << xns::is_class<decltype(test_function_is_class)> << std::endl;
	std::cout << "is_class [void]: " << xns::is_class<void> << std::endl;
	std::cout << "is_class [void*]: " << xns::is_class<void*> << std::endl;

	return 0;
}

#if defined(XNS_TEST_IS_CLASS)
int main(void) {
	return unit_tests_is_class();
}
#endif

