#include "unit_tests.hpp"

void numeric_limits_tests(void) {
	// avoid namespace pollution
	using namespace std;

	//cout << "bool MIN:                " << Xf::min<bool>() << endl;
	//cout << "bool MAX:                " << Xf::max<bool>() << endl;
	cout << "char8_t MIN:             " << Xf::min<char8_t>() << endl;
	cout << "char8_t MAX:             " << Xf::max<char8_t>() << endl;
	cout << "char16_t MIN:            " << Xf::min<char16_t>() << endl;
	cout << "char16_t MAX:            " << Xf::max<char16_t>() << endl;
	cout << "char32_t MIN:            " << Xf::min<char32_t>() << endl;
	cout << "char32_t MAX:            " << Xf::max<char32_t>() << endl;
	cout << "wchar_t MIN:             " << Xf::min<wchar_t>() << endl;
	cout << "wchar_t MAX:             " << Xf::max<wchar_t>() << endl;
	cout << "char MIN:                " << Xf::min<char>() << endl;
	cout << "char MAX:                " << Xf::max<char>() << endl;
	cout << "short MIN:               " << Xf::min<short>() << endl;
	cout << "short MAX:               " << Xf::max<short>() << endl;
	cout << "int MIN:                 " << Xf::min<int>() << endl;
	cout << "int MAX:                 " << Xf::max<int>() << endl;
	cout << "long MIN:                " << Xf::min<long>() << endl;
	cout << "long MAX:                " << Xf::max<long>() << endl;
	cout << "long long MIN:           " << Xf::min<long long>() << endl;
	cout << "long long MAX:           " << Xf::max<long long>() << endl;
	cout << "unsigned char MIN:       " << Xf::min<unsigned char>() << endl;
	cout << "unsigned char MAX:       " << Xf::max<unsigned char>() << endl;
	cout << "unsigned short MIN:      " << Xf::min<unsigned short>() << endl;
	cout << "unsigned short MAX:      " << Xf::max<unsigned short>() << endl;
	cout << "unsigned int MIN:        " << Xf::min<unsigned int>() << endl;
	cout << "unsigned int MAX:        " << Xf::max<unsigned int>() << endl;
	cout << "unsigned long MIN:       " << Xf::min<unsigned long>() << endl;
	cout << "unsigned long MAX:       " << Xf::max<const unsigned long>() << endl;
	cout << "unsigned long long MIN:  " << Xf::min<unsigned long long>() << endl;
	cout << "unsigned long long MAX:  " << Xf::max<unsigned long long>() << endl;

	auto max = Xf::max_digits<unsigned char>();
	std::cout << "max digits: " << (int)max << std::endl;
	auto min = Xf::min_digits<unsigned char>();
	std::cout << "min digits: " << (int)min << std::endl;
}
