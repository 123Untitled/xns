#include "unit_tests.hpp"
#include "is_signed.hpp"

#include <unistd.h>
#include <type_traits>
#include "string_literal.hpp"


template <xns::basic_string_literal msg, class T, bool expected>
static bool checker(void) {

	// print test
	write(STDOUT_FILENO, msg.data(), msg.size());

	// check if the result is the expected one
	constexpr bool result = xns::is_signed<T>;
	// standard result
	constexpr bool std_result = std::is_signed<T>::value;
	// all tests
	constexpr bool all_tests = result == std_result == expected;


	if constexpr (all_tests) {
		write(STDOUT_FILENO, " \x1b[32msuccess\x1b[0m", 17);

		if constexpr (result == true) { write(STDOUT_FILENO, " [true]\n", 8);  }
		else                          { write(STDOUT_FILENO, " [false]\n", 9); }
	}

	else {
		write(STDOUT_FILENO, " \x1b[31mfailure\x1b[0m", 17);

		if constexpr (result     == true) { write(STDOUT_FILENO, " result: [true]", 15);  }
		else                              { write(STDOUT_FILENO, " result: [false]", 16); }
		if constexpr (std_result == true) { write(STDOUT_FILENO, " std_result: [true]", 19);  }
		else                              { write(STDOUT_FILENO, " std_result: [false]", 20); }
		if constexpr (expected   == true) { write(STDOUT_FILENO, " expected: [true]", 16);  }
		else                              { write(STDOUT_FILENO, " expected: [false]", 18); }

		write(STDOUT_FILENO, "\n", 1);

	}



	return all_tests;
}


/* unit test */

auto unit_tests_is_signed(void) -> int {

	//UT::print<0x00ff00>("test_print: ", 23.5, "\n");

	return

	   checker<"char               ->", char,               false>()
	&& checker<"signed char        ->", signed char,        true>()
	&& checker<"unsigned char      ->", unsigned char,      false>()
	&& checker<"short              ->", short,              true>()
	&& checker<"unsigned short     ->", unsigned short,     false>()
	&& checker<"int                ->", int,                true>()
	&& checker<"unsigned int       ->", unsigned int,       false>()
	&& checker<"long               ->", long,               true>()
	&& checker<"unsigned long      ->", unsigned long,      false>()
	&& checker<"long long          ->", long long,          true>()
	&& checker<"unsigned long long ->", unsigned long long, false>()

	&& checker<"float              ->", float,              true>()
	&& checker<"double             ->", double,             true>()
	&& checker<"long double        ->", long double,        true>()

	&& checker<"bool               ->", bool,               false>()

	&& checker<"char8_t            ->", char8_t,            false>()
	&& checker<"char16_t           ->", char16_t,           false>()
	&& checker<"char32_t           ->", char32_t,           false>()
	&& checker<"wchar_t            ->", wchar_t,            false>();

	return 0;
}

#if defined(XNS_TEST_IS_SIGNED)
int main(void) {
	return unit_tests_is_signed();
}
#endif


