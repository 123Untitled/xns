#include "unit_tests.hpp"
#include "xns/utility/numeric_limits.hpp"
#include "xns/other/base.hpp"
#include <limits>


template <class... A>
void limits(const A&... args) {
	((std::cout << args << "\n"), ...);
}



auto unit_tests_numeric_limits(void) -> int {

	// avoid namespace pollution
	using namespace std;

	//UT::print<"bool">();
	cout << "min: " << xns::limits<bool>::min() << "\n";
	cout << "max: " << xns::limits<bool>::max() << "\n\n";

	//UT::print<"char8_t">();
	cout << "min: " << (long long)xns::limits<char8_t>::min() << "\n";
	cout << "max: " << (long long)xns::limits<char8_t>::max() << "\n\n";

	//UT::print<"char16_t">();
	cout << "min: " << (long long)xns::limits<char16_t>::min() << "\n";
	cout << "max: " << (long long)xns::limits<char16_t>::max() << "\n\n";

	//UT::print<"char32_t">();
	cout << "min: " << (long long)xns::limits<char32_t>::min() << "\n";
	cout << "max: " << (long long)xns::limits<char32_t>::max() << "\n\n";

	//UT::print<"wchar_t">();
	cout << "min: " << (long long)xns::limits<wchar_t>::min() << "\n";
	cout << "max: " << (long long)xns::limits<wchar_t>::max() << "\n\n";

	//UT::print<"char">();
	cout << "min: " << (long long)xns::limits<char>::min() << "\n";
	cout << "max: " << (long long)xns::limits<char>::max() << "\n\n";

	//UT::print<"signed char">();
	cout << "min: " << (long long)xns::limits<signed char>::min() << "\n";
	cout << "max: " << (long long)xns::limits<signed char>::max() << "\n\n";

	//UT::print<"unsigned char">();
	cout << "min: " << (long long)xns::limits<unsigned char>::min() << "\n";
	cout << "max: " << (long long)xns::limits<unsigned char>::max() << "\n\n";

	//UT::print<"short">();
	cout << "min: " << xns::limits<short>::min() << "\n";
	cout << "max: " << xns::limits<short>::max() << "\n\n";

	//UT::print<"unsigned short">();
	cout << "min: " << xns::limits<unsigned short>::min() << "\n";
	cout << "max: " << xns::limits<unsigned short>::max() << "\n\n";

	//UT::print<"int">();
	cout << "min: " << xns::limits<int>::min() << "\n";
	cout << "max: " << xns::limits<int>::max() << "\n\n";

	//UT::print<"unsigned int">();
	cout << "min: " << xns::limits<unsigned int>::min() << "\n";
	cout << "max: " << xns::limits<unsigned int>::max() << "\n\n";

	//UT::print<"long">();
	cout << "min: " << xns::limits<long>::min() << "\n";
	cout << "max: " << xns::limits<long>::max() << "\n\n";

	//UT::print<"unsigned long">();
	cout << "min: " << xns::limits<unsigned long>::min() << "\n";
	cout << "max: " << xns::limits<unsigned long>::max() << "\n\n";

	//UT::print<"long long">();
	cout << "min: " << xns::limits<long long>::min() << "\n";
	cout << "max: " << xns::limits<long long>::max() << "\n\n";

	//UT::print<"unsigned long long">();
	cout << "min: " << xns::limits<unsigned long long>::min() << "\n";
	cout << "max: " << xns::limits<unsigned long long>::max() << "\n\n";


	auto max = xns::limits<char>::digits<xns::bin>();
	std::cout << "max digits: " << (int)max << std::endl;

	using namespace xns;

	//std::cout << "static digits: " << xns::limits<unsigned int>::digits<10, xns::dec>() << std::endl;


	//std::cout << "max float: " << xns::limits<float>::max() << std::endl;
	//std::cout << "min float: " << xns::limits<float>::min() << std::endl;
	//std::cout << "max float (std): " << std::numeric_limits<float>::max() << std::endl;
	//std::cout << "min float (std): " << std::numeric_limits<float>::min() << std::endl;


	return 0;
}



#if defined(XNS_TEST_NUMERIC_LIMITS)
int main(void) {
	return unit_tests_numeric_limits();
}
#endif

