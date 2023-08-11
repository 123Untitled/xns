#include "unit_tests.hpp"
#include "is_integral.hpp"

// avoid namespace pollution
using namespace xns;

template <bool expected>
void test(const bool result, const char* msg) {

	// get the boolean as a string
	const char* boolean = result ? "true  " : "false ";

	// print the result
	std::cout   << std::setw(20)
				<< std::right << msg << " "
				<< boolean;

	// print the expected result
	if (result == expected)
		std::cout << "\x1b[32msuccess\x1b[0m" << std::endl;
	else
		std::cout << "\x1b[31mfailure\x1b[0m" << std::endl;
}


/* unit test */
template <>
bool UT::unit_tests<"is_integral">(void) {

	test<true >(is_integral<char>,               "char");
	test<true >(is_integral<signed char>,        "signed char");
	test<true >(is_integral<unsigned char>,      "unsigned char");
	test<true >(is_integral<short>,              "short");
	test<true >(is_integral<unsigned short>,     "unsigned short");
	test<true >(is_integral<int>,                "int");
	test<true >(is_integral<unsigned int>,       "unsigned int");
	test<true >(is_integral<long>,               "long");
	test<true >(is_integral<unsigned long>,      "unsigned long");
	test<true >(is_integral<long long>,          "long long");
	test<true >(is_integral<unsigned long long>, "unsigned long long");
	test<true >(is_integral<char8_t>,            "char8_t");
	test<true >(is_integral<char16_t>,           "char16_t");
	test<true >(is_integral<char32_t>,           "char32_t");
	test<true >(is_integral<wchar_t>,            "wchar_t");
	test<true >(is_integral<bool>,               "bool");

	test<false>(is_integral<float>,              "float");
	test<false>(is_integral<double>,             "double");
	test<false>(is_integral<long double>,        "long double");
	test<false>(is_integral<void>,               "void");
	test<false>(is_integral<int*>,               "int*");
	test<false>(is_integral<int&>,               "int&");
	test<false>(is_integral<int&&>,              "int&&");
	test<false>(is_integral<int[]>,              "int[]");
	test<false>(is_integral<int[5]>,             "int[5]");
	test<false>(is_integral<int(*)[5]>,          "int(*)[5]");
	test<false>(is_integral<int(&)[5]>,          "int(&)[5]");
	test<false>(is_integral<int(*)[]>,           "int(*)[]");

	test<true >(is_integral<const char>,         "const char");
	test<true >(is_integral<volatile char>,      "volatile char");
	test<true >(is_integral<const volatile char>,"const volatile char");
	// code here...
	return false;
}

int main(void) {
	UT::unit_tests<"is_integral">();
	return 0;
}
