#include "unit_tests.hpp"

#if (defined XNS_UT) && (META_UT)
int main(void) { return UT::meta_ut(); }
#endif

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


template <>
bool UT::unit_tests<"meta">(void) {

	/*

	tests::base base;

	tests::derived derived;

	test<true >(is_derived_from<tests::derived, tests::base>, "derived -> base");
	test<false>(is_derived_from<tests::base,    tests::derived>, "base -> derived");
	test<true>(is_derived_from<tests::base,    tests::base>, "base -> base");
	test<true>(is_derived_from<tests::derived, tests::derived>, "derived -> derived");

	// std version

	test<true >(std::derived_from<tests::derived, tests::base>, "derived -> base");
	test<false>(std::derived_from<tests::base,    tests::derived>, "base -> derived");
	test<true>(std::derived_from<tests::base,    tests::base>, "base -> base");
	test<true>(std::derived_from<tests::derived, tests::derived>, "derived -> derived");


	START_UT("is_base_of");

	test<true >(is_base_of<tests::base,    tests::derived>, "base -> derived");
	test<false>(is_base_of<tests::derived, tests::base>, "derived -> base");
	test<true >(is_base_of<tests::base,    tests::base>, "base -> base");
	test<true >(is_base_of<tests::derived, tests::derived>, "derived -> derived");

	// std version

	test<true >(std::is_base_of_v<tests::base,    tests::derived>, "base -> derived");
	test<false>(std::is_base_of_v<tests::derived, tests::base>, "derived -> base");
	test<true >(std::is_base_of_v<tests::base,    tests::base>, "base -> base");
	test<true >(std::is_base_of_v<tests::derived, tests::derived>, "derived -> derived");

	return true;






	START_UT("is_integral");


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


	START_UT("is_array");


	test<true >(is_array<int[]>,          "int[]");
	test<true >(is_array<int[5]>,         "int[5]");
	test<false>(is_array<int(*)[5]>,      "int(*)[5]");
	test<false>(is_array<int(&)[5]>,      "int(&)[5]");
	test<false>(is_array<int(*)[]>,       "int(*)[]");
	test<false>(is_array<int>,            "int");
	test<false>(is_array<int&>,           "int&");
	test<false>(is_array<int*>,           "int*");
	test<true >(is_array<const int[]>,    "const int[]");
	test<true >(is_array<volatile int[]>, "volatile int[]");
	test<true >(is_array<const volatile int[]>, "const volatile int[]");


	START_UT("is_pointer");

	test<false>(is_pointer<int[]>,          "int[]");
	test<false>(is_pointer<int[5]>,         "int[5]");
	test<true >(is_pointer<int(*)[5]>,      "int(*)[5]");
	test<false>(is_pointer<int(&)[5]>,      "int(&)[5]");
	test<true >(is_pointer<int(*)[]>,       "int(*)[]");
	test<false>(is_pointer<int>,            "int");
	test<false>(is_pointer<int&>,           "int&");
	test<true >(is_pointer<int*>,           "int*");
	test<true >(is_pointer<const int*>,     "const int*");
	test<true >(is_pointer<volatile int*>,  "volatile int*");
	test<true >(is_pointer<const volatile int*>, "const volatile int*");
	test<true >(is_pointer<const int* const>,     "const int* const");
	test<true >(is_pointer<volatile int* const>,  "volatile int* const");
	test<true >(is_pointer<const volatile int* const>, "const volatile int* const");
	test<true >(is_pointer<const int* volatile>,     "const int* volatile");
	test<true >(is_pointer<volatile int* volatile>,  "volatile int* volatile");
	test<true >(is_pointer<const volatile int* volatile>, "const volatile int* volatile");

	START_UT("std::is_pointer");

	test<false>(std::is_pointer<int[]>::value,          "int[]");
	test<false>(std::is_pointer<int[5]>::value,         "int[5]");
	test<true >(std::is_pointer<int(*)[5]>::value,      "int(*)[5]");
	test<false>(std::is_pointer<int(&)[5]>::value,      "int(&)[5]");
	test<true >(std::is_pointer<int(*)[]>::value,       "int(*)[]");
	test<false>(std::is_pointer<int>::value,            "int");
	test<false>(std::is_pointer<int&>::value,           "int&");
	test<true >(std::is_pointer<int*>::value,           "int*");
	test<true >(std::is_pointer<const int*>::value,     "const int*");
	test<true >(std::is_pointer<volatile int*>::value,  "volatile int*");
	test<true >(std::is_pointer<const volatile int*>::value, "const volatile int*");
	test<true >(std::is_pointer<const int* const>::value,     "const int* const");
	test<true >(std::is_pointer<volatile int* const>::value,  "volatile int* const");
	test<true >(std::is_pointer<const volatile int* const>::value, "const volatile int* const");
	test<true >(std::is_pointer<const int* volatile>::value,     "const int* volatile");
	test<true >(std::is_pointer<volatile int* volatile>::value,  "volatile int* volatile");
	test<true >(std::is_pointer<const volatile int* volatile>::value, "const volatile int* volatile");
	*/

	return EXIT_SUCCESS;

}
