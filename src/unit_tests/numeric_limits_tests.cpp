#include "unit_tests.hpp"
#include "numeric_limits.hpp"

template <>
bool UT::unit_tests<"numeric_limits">(void) {

	// avoid namespace pollution
	using namespace std;

	//cout << "bool MIN:                " << Xf::min<bool>() << endl;
	//cout << "bool MAX:                " << Xf::max<bool>() << endl;
	cout << "char8_t MIN:             " << (long long)xns::min<char8_t>() << endl;
	cout << "char8_t MAX:             " << (long long)xns::max<char8_t>() << endl;
	cout << "char16_t MIN:            " << (long long)xns::min<char16_t>() << endl;
	cout << "char16_t MAX:            " << (long long)xns::max<char16_t>() << endl;
	cout << "char32_t MIN:            " << (long long)xns::min<char32_t>() << endl;
	cout << "char32_t MAX:            " << (long long)xns::max<char32_t>() << endl;
	cout << "wchar_t MIN:             " << (long long)xns::min<wchar_t>() << endl;
	cout << "wchar_t MAX:             " << (long long)xns::max<wchar_t>() << endl;
	cout << "char MIN:                " << (long long)xns::min<char>() << endl;
	cout << "char MAX:                " << (long long)xns::max<char>() << endl;
	cout << "short MIN:               " << (long long)xns::min<short>() << endl;
	cout << "short MAX:               " << (long long)xns::max<short>() << endl;
	cout << "int MIN:                 " << (long long)xns::min<int>() << endl;
	cout << "int MAX:                 " << (long long)xns::max<int>() << endl;
	cout << "long MIN:                " << (long long)xns::min<long>() << endl;
	cout << "long MAX:                " << (long long)xns::max<long>() << endl;
	cout << "long long MIN:           " << (long long)xns::min<long long>() << endl;
	cout << "long long MAX:           " << (long long)xns::max<long long>() << endl;
	cout << "unsigned char MIN:       " << (long long)xns::min<unsigned char>() << endl;
	cout << "unsigned char MAX:       " << (long long)xns::max<unsigned char>() << endl;
	cout << "unsigned short MIN:      " << (long long)xns::min<unsigned short>() << endl;
	cout << "unsigned short MAX:      " << (long long)xns::max<unsigned short>() << endl;
	cout << "unsigned int MIN:        " << (long long)xns::min<unsigned int>() << endl;
	cout << "unsigned int MAX:        " << (long long)xns::max<unsigned int>() << endl;
	cout << "unsigned long MIN:       " << (long long)xns::min<unsigned long>() << endl;
	cout << "unsigned long MAX:       " << (long long)xns::max<const unsigned long>() << endl;
	cout << "unsigned long long MIN:  " << (long long)xns::min<unsigned long long>() << endl;
	cout << "unsigned long long MAX:  " << (long long)xns::max<unsigned long long>() << endl;

	auto max = xns::max_digits<unsigned char>();
	std::cout << "max digits: " << (int)max << std::endl;
	auto min = xns::min_digits<unsigned char>();
	std::cout << "min digits: " << (int)min << std::endl;
	return true;
}
