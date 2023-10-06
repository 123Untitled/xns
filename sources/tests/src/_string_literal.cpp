#include "unit_tests.hpp"

//#include "literal_map.hpp"

#include "string_literal.hpp"

//template <xns::u8string_literal str1, xns::u8string_literal str2>
//consteval auto test(void) -> bool {
//	return str1 == str2;
//}
//
//template <xns::basic_string_literal str>
//consteval auto test_literal(void) -> void {
//}

template <>
int UT::unit_tests<"string_literal">(void) {
	// code here...
	return 0;
}

#if defined(XNS_TEST_STRING_LITERAL)
int main(void) {
	return UT::unit_tests<"string_literal">();
}
#endif


	//constexpr xns::string_literal s{"hello"};

	//test_literal<s>();

	//constexpr xns::string_literal s9{s};



	//constexpr bool b = test<u8"hello", u8"hello">();

	//constexpr xns::string_literal s3{"hello"};
	//constexpr xns::string_literal s4 = "hello";

	//constexpr xns::basic_string_literal<char, 5> s2{s};




	// WARNING: need to fix char_sequence !!!
	//xns::literal_map<int, "hello", U"world", u8"!" > map{};

