#include "unit_tests.hpp"
#include "type_traits/relationships_and_property_queries/is_same.hpp"



template <bool expected, typename... A>
static auto is_same_test(const char* msg) -> void {
	ut::test<expected, xns::is_same<A...>>(msg);
}

template <bool expected, typename... A>
static auto is_same_cvr_test(const char* msg) -> void {
	ut::test<expected, xns::is_same_cvr<A...>>(msg);
}


/* unit test */

auto unit_tests_is_same(void) -> int {


	is_same_test<true, int, int>("int, int");
	is_same_test<true, char, char>("char, char");
	is_same_test<false, int, char>("int, char");
	is_same_test<false, double, float>("double, float");
	is_same_test<false, int, const int>("int, const int");
	is_same_test<false, char, volatile char>("char, volatile char");
	is_same_test<false, double, double&>("double, double&");
	is_same_test<false, float, float&&>("float, float&&");
	is_same_test<true, int, int, int>("int, int, int");
	is_same_test<false, int, int, char>("int, int, char");
	is_same_test<false, int, int, const int>("int, int, const int");
	is_same_test<false, int, int, volatile int>("int, int, volatile int");
	is_same_test<true, const int, const int, const int>("const int, const int, const int");
	is_same_test<false, const int, const int, int>("const int, const int, int");
    is_same_test<false, int, unsigned int>("int, unsigned int");
    is_same_test<false, long, long long>("long, long long");
    is_same_test<false, float, double>("float, double");
    is_same_test<false, char*, char* const>("char*, char* const");
    is_same_test<false, int[5], int[10]>("int[5], int[10]");
    is_same_test<false, int*, int&>("int*, int&");
    is_same_test<true, void(*)(), void(*)()>("void(*)(), void(*)()");
    is_same_test<false, int(*)(int), double(*)(double)>("int(*)(int), double(*)(double)");
	is_same_test<true, int(*)(int), int(*)(int)>("int(*)(int), int(*)(int)");
    is_same_test<false, int, unsigned int, int>("int, unsigned int, int");
    is_same_test<false, char, char, int>("char, char, int");
	is_same_test<true, int, int, int, int, int, int, int, int>("int, int, int, int, int, int, int, int");



    is_same_cvr_test<true, int, int>("int, int");
    is_same_cvr_test<true, char, char>("char, char");
    is_same_cvr_test<false, int, char>("int, char");
    is_same_cvr_test<false, double, float>("double, float");
    is_same_cvr_test<true, int, const int>("int, const int");
    is_same_cvr_test<true, char, volatile char>("char, volatile char");
    is_same_cvr_test<true, double, double&>("double, double&");
    is_same_cvr_test<true, float, float&&>("float, float&&");
    is_same_cvr_test<true, int, int, int>("int, int, int");
    is_same_cvr_test<false, int, int, char>("int, int, char");
    is_same_cvr_test<false, int, unsigned int>("int, unsigned int");
    is_same_cvr_test<false, long, long long>("long, long long");
    is_same_cvr_test<false, float, double>("float, double");
    is_same_cvr_test<true, char*, char* const>("char*, char* const");
    is_same_cvr_test<false, int[5], int[10]>("int[5], int[10]");
    is_same_cvr_test<false, int*, int&>("int*, int&");
    is_same_cvr_test<true, void(*)(), void(*)()>("void(*)(), void(*)()");
    is_same_cvr_test<false, int(*)(int), double(*)(double)>("int(*)(int), double(*)(double)");
    is_same_cvr_test<false, int, unsigned int, int>("int, unsigned int, int");
    is_same_cvr_test<false, char, char, int>("char, char, int");



	return 0;
}

#if defined(XNS_TEST_IS_SAME)
int main(void) {
	return unit_tests_is_same();
}
#endif


