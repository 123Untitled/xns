#include "unit_tests.hpp"
#include "numeric_limits.hpp"
#include "base.hpp"


template <class... A>
void limits(const A&... args) {
	((std::cout << args << "\n"), ...);
}


template <>
int UT::unit_tests<"numeric_limits">(void) {

	// avoid namespace pollution
	using namespace std;

	UT::print<"bool">();
	cout << "min: " << xns::limits::min<bool>() << "\n";
	cout << "max: " << xns::limits::max<bool>() << "\n\n";

	UT::print<"char8_t">();
	cout << "min: " << (long long)xns::limits::min<char8_t>() << "\n";
	cout << "max: " << (long long)xns::limits::max<char8_t>() << "\n\n";

	UT::print<"char16_t">();
	cout << "min: " << (long long)xns::limits::min<char16_t>() << "\n";
	cout << "max: " << (long long)xns::limits::max<char16_t>() << "\n\n";

	UT::print<"char32_t">();
	cout << "min: " << (long long)xns::limits::min<char32_t>() << "\n";
	cout << "max: " << (long long)xns::limits::max<char32_t>() << "\n\n";

	UT::print<"wchar_t">();
	cout << "min: " << (long long)xns::limits::min<wchar_t>() << "\n";
	cout << "max: " << (long long)xns::limits::max<wchar_t>() << "\n\n";

	UT::print<"char">();
	cout << "min: " << (long long)xns::limits::min<char>() << "\n";
	cout << "max: " << (long long)xns::limits::max<char>() << "\n\n";

	UT::print<"signed char">();
	cout << "min: " << (long long)xns::limits::min<signed char>() << "\n";
	cout << "max: " << (long long)xns::limits::max<signed char>() << "\n\n";

	UT::print<"unsigned char">();
	cout << "min: " << (long long)xns::limits::min<unsigned char>() << "\n";
	cout << "max: " << (long long)xns::limits::max<unsigned char>() << "\n\n";

	UT::print<"short">();
	cout << "min: " << xns::limits::min<short>() << "\n";
	cout << "max: " << xns::limits::max<short>() << "\n\n";

	UT::print<"unsigned short">();
	cout << "min: " << xns::limits::min<unsigned short>() << "\n";
	cout << "max: " << xns::limits::max<unsigned short>() << "\n\n";

	UT::print<"int">();
	cout << "min: " << xns::limits::min<int>() << "\n";
	cout << "max: " << xns::limits::max<int>() << "\n\n";

	UT::print<"unsigned int">();
	cout << "min: " << xns::limits::min<unsigned int>() << "\n";
	cout << "max: " << xns::limits::max<unsigned int>() << "\n\n";

	UT::print<"long">();
	cout << "min: " << xns::limits::min<long>() << "\n";
	cout << "max: " << xns::limits::max<long>() << "\n\n";

	UT::print<"unsigned long">();
	cout << "min: " << xns::limits::min<unsigned long>() << "\n";
	cout << "max: " << xns::limits::max<const unsigned long>() << "\n\n";

	UT::print<"long long">();
	cout << "min: " << xns::limits::min<long long>() << "\n";
	cout << "max: " << xns::limits::max<long long>() << "\n\n";

	UT::print<"unsigned long long">();
	cout << "min: " << xns::limits::min<unsigned long long>() << "\n";
	cout << "max: " << xns::limits::max<unsigned long long>() << "\n\n";


	auto max = xns::limits::digits<char, xns::bin>();
	std::cout << "max digits: " << (int)max << std::endl;

	using namespace xns;

	std::cout << "static digits: " << limits::digits<10, xns::dec>() << std::endl;


	return 0;
}



#if defined(XNS_TEST_NUMERIC_LIMITS)
int main(void) {
	return UT::unit_tests<"numeric_limits">();
}
#endif

