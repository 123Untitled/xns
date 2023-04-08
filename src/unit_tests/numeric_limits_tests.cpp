#include "unit_tests.hpp"

void numeric_limits_tests(void) {
	// avoid namespace pollution
	using namespace std;

	//cout << "bool MIN:                " << Xf::min<bool>() << endl;
	//cout << "bool MAX:                " << Xf::max<bool>() << endl;
	cout << "char8_t MIN:             " << (long long)Xf::min<char8_t>() << endl;
	cout << "char8_t MAX:             " << (long long)Xf::max<char8_t>() << endl;
	cout << "char16_t MIN:            " << (long long)Xf::min<char16_t>() << endl;
	cout << "char16_t MAX:            " << (long long)Xf::max<char16_t>() << endl;
	cout << "char32_t MIN:            " << (long long)Xf::min<char32_t>() << endl;
	cout << "char32_t MAX:            " << (long long)Xf::max<char32_t>() << endl;
	cout << "wchar_t MIN:             " << (long long)Xf::min<wchar_t>() << endl;
	cout << "wchar_t MAX:             " << (long long)Xf::max<wchar_t>() << endl;
	cout << "char MIN:                " << (long long)Xf::min<char>() << endl;
	cout << "char MAX:                " << (long long)Xf::max<char>() << endl;
	cout << "short MIN:               " << (long long)Xf::min<short>() << endl;
	cout << "short MAX:               " << (long long)Xf::max<short>() << endl;
	cout << "int MIN:                 " << (long long)Xf::min<int>() << endl;
	cout << "int MAX:                 " << (long long)Xf::max<int>() << endl;
	cout << "long MIN:                " << (long long)Xf::min<long>() << endl;
	cout << "long MAX:                " << (long long)Xf::max<long>() << endl;
	cout << "long long MIN:           " << (long long)Xf::min<long long>() << endl;
	cout << "long long MAX:           " << (long long)Xf::max<long long>() << endl;
	cout << "unsigned char MIN:       " << (long long)Xf::min<unsigned char>() << endl;
	cout << "unsigned char MAX:       " << (long long)Xf::max<unsigned char>() << endl;
	cout << "unsigned short MIN:      " << (long long)Xf::min<unsigned short>() << endl;
	cout << "unsigned short MAX:      " << (long long)Xf::max<unsigned short>() << endl;
	cout << "unsigned int MIN:        " << (long long)Xf::min<unsigned int>() << endl;
	cout << "unsigned int MAX:        " << (long long)Xf::max<unsigned int>() << endl;
	cout << "unsigned long MIN:       " << (long long)Xf::min<unsigned long>() << endl;
	cout << "unsigned long MAX:       " << (long long)Xf::max<const unsigned long>() << endl;
	cout << "unsigned long long MIN:  " << (long long)Xf::min<unsigned long long>() << endl;
	cout << "unsigned long long MAX:  " << (long long)Xf::max<unsigned long long>() << endl;

	auto max = Xf::max_digits<unsigned char>();
	std::cout << "max digits: " << (int)max << std::endl;
	auto min = Xf::min_digits<unsigned char>();
	std::cout << "min digits: " << (int)min << std::endl;
}
