#include "type_traits/type_properties/is_referenceable.hpp"
#include "config/config.hpp"
#include <iostream>


template <typename T, bool expected, decltype(sizeof(0)) N>
static auto check(const char(&msg)[N]) noexcept -> int {

	constexpr bool is_ref0 = xns::is_referenceable<T>;
#if XNS_HAS_BUILTIN(__is_referenceable)
	constexpr bool is_ref1 = __is_referenceable(T);
#else
	constexpr bool is_ref1 = false;
#endif

	if (is_ref0 != is_ref1 && is_ref0 != expected) {
		std::cout << "\x1b[31mfailed\x1b[0m " << msg << std::endl;
	}
	else {
		std::cout << "\x1b[32msuccess\x1b[0m " << msg << std::endl;
	}


	return 0;
}

class test {
};

/* unit test */
int unit_tests_is_referenceable(void) {

	/* true */
	check<int, false>("int");
	check<int&, true>("int&");
	check<int&&, true>("int&&");
	check<int*, true>("int*");
	check<int**, true>("int**");
	check<int*&, true>("int*&");
	check<int*&&, true>("int*&&");
	check<int[], true>("int[]");
	check<int[1], true>("int[1]");
	check<int[1][1], true>("int[1][1]");
	check<int[1][1][1], true>("int[1][1][1]");
	check<void*, true>("void*");
	check<void**, true>("void**");
	check<void(*&)(void), true>("void(*&)(void)");
	check<void(*)(void), true>("void(*)(void)");

	/* false */
	check<void, false>("void");
	check<int(test::*)(double), false>("int(test::*)(double)");





	return 0;
}

#if defined(XNS_TEST_IS_REFERENCEABLE)
int main(void) {
	return unit_tests_is_referenceable();
}
#endif

