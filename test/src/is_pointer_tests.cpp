#include "unit_tests.hpp"
#include "is_pointer.hpp"

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
bool UT::unit_tests<"is_pointer">(void) {


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
	// code here...
	return false;
}

int main(void) {
	return UT::unit_tests<"is_pointer">();
}
