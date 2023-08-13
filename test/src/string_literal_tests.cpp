//#include "unit_tests.hpp"

//#include "literal_map.hpp"

#include "string_literal.hpp"

template <xns::u8string_literal str1, xns::u8string_literal str2>
consteval auto test(void) -> bool {
	return str1 == str2;
}

int main(void) {

	constexpr bool b = test<u8"hello", u8"hello">();


	return 0;


	// WARNING: need to fix char_sequence !!!
	//xns::literal_map<int, "hello", U"world", u8"!" > map{};

}
