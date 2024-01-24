#include "unit_tests.hpp"

//#include "literal_map.hpp"

#include "string_literal.hpp"


template <xns::basic_string_literal str>
consteval auto test0(void) -> bool {
	return false;
	//return str == "hello";
	//return "hello" != str;
}

template <xns::basic_string_literal str1, xns::basic_string_literal str2>
consteval auto test1(void) -> bool {

	//auto a = str1[40000];
	return false;

	//return str1 == str2;
	//return str1 != str2;
}

template <>
int UT::unit_tests<"string_literal">(void) {

	using arr_ref = const char(&)[6];

	constexpr xns::basic_string_literal str1{u8"hello"};
	constexpr xns::basic_string_literal str2{"hello"};

	if (str1 <= str2) {
		std::cout << "str1 == str2" << std::endl;
	}


	//constexpr arr_ref arr1 = str1;


	//test0<"hello">(); // work
	//test1<"hello", "hello">(); // work
	//
	//constexpr char arr1[] = "hello";
	//constexpr char arr2[] = "heilo";
	//
	//constexpr bool b = xns::compare(arr1, arr2);
	//
	//std::cout << b << std::endl;

	return 0;


	//constexpr xns::string_literal s{"hello"};

	//test_literal<s>();

	//constexpr xns::string_literal s9{s};



	//constexpr bool b = test<u8"hello", u8"hello">();

	//constexpr xns::string_literal s3{"hello"};
	//constexpr xns::string_literal s4 = "hello";

	//constexpr xns::basic_string_literal<char, 5> s2{s};

	// WARNING: need to fix char_sequence !!!
	//xns::literal_map<int, "hello", U"world", u8"!" > map{};

	// code here...
	return 0;
}


#if defined(XNS_TEST_STRING_LITERAL)
int main(void) {
	return UT::unit_tests<"string_literal">();
}
#endif

