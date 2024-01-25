#include "unit_tests.hpp"
#include "is_one_of.hpp"




template <bool expected, typename T, typename... A>
static auto is_one_of(const char* msg) -> void {
	ut::test<expected, xns::is_one_of<T, A...>>(msg);
}

/* unit test */

auto unit_tests_is_one_of(void) -> int {


	is_one_of<true, int, int, int>("int, int, int");
	is_one_of<true, char, char, float>("char, char, float");
	is_one_of<false, int, long, char>("int, long, char");
	is_one_of<false, int, char, const int>("int, char, const int");
	is_one_of<false, int, int&, int*>("int, int&, int*");


	return 0;
}

#if defined(XNS_TEST_IS_ONE_OF)
int main(void) {
	return unit_tests_is_one_of();
}
#endif

